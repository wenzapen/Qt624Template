#ifndef FORWARD_H
#define FORWARD_H

#include <decoders.h>


template<IDemuxDecoder::DecoderType type>
class DecoderImpl : public DecoderContext, public IDemuxDecoder {
protected:
    TwinsBlockQueue<AVFrame *> *frameQueue;
public:
    DecoderImpl(AVStream *vs, TwinsBlockQueue<AVFrame *> *queue)
        : DecoderContext(vs), frameQueue(queue) {}

    YT20_THREAD_SAFE double duration() override {
        return static_cast<double>(stream->duration) * av_q2d(stream->time_base);
    }

    YT20_GUARD_BY(DECODER) bool accept(AVPacket *pkt, std::atomic<bool> &interrupt) override {
        if (!frameQueue->isEnable())
            return true;
        int ret = avcodec_send_packet(codecCtx, pkt);
        if (ret < 0) {
            qWarning() << "Error avcodec_send_packet:" << ffmpegErrToString(ret);
            return false;
        }
        while(ret >= 0 && !interrupt) {
            ret = avcodec_receive_frame(codecCtx, frameBuf);
            if (ret >= 0) {

                // 检查帧是否为硬件格式，如果是，转换为CPU兼容格式
                if (DecoderContext::hwPixFmt != AV_PIX_FMT_NONE && frameBuf->format == DecoderContext::hwPixFmt) {

                    //hardware decoder
                    if (av_hwframe_transfer_data(cpuFrame, frameBuf, 0) < 0) {
                        qWarning() << "Failed to transfer frame to CPU.";
                        av_frame_unref(cpuFrame);
                        av_frame_unref(frameBuf);
                        return false;
                    }
                    cpuFrame->pts = frameBuf->pts;

                    if (!frameQueue->push(cpuFrame)) {
                        qDebug() << "push failure";
                        frameQueue->clear([](AVFrame *frame) { av_frame_free(&frame); });
                        av_frame_unref(cpuFrame);
                        av_frame_unref(frameBuf);  // 释放临时的CPU帧
                        return false;
                    }
                    cpuFrame = av_frame_alloc();
                    // cpuFrame->format = AV_PIX_FMT_YUV420P;

                    // if (!frameQueue->push(frameBuf)) {
                    //     frameQueue->clear([](AVFrame *frame) { av_frame_free(&frame); });
                    //     av_frame_unref(frameBuf);
                    //     return false;
                    // }
                    // qDebug() << "SW decode sucesss";
                    // frameBuf = av_frame_alloc();

                } else {

                    if (!frameQueue->push(frameBuf)) {
                        frameQueue->clear([](AVFrame *frame) { av_frame_free(&frame); });
                        av_frame_unref(frameBuf);
                        return false;
                    }
                    // qDebug() << "SW decode sucesss";
                    frameBuf = av_frame_alloc();
                }

            } else if (ret == AVERROR(EAGAIN)) {
                return true;
            } else if (ret == ERROR_EOF) {
                frameQueue->push(nullptr);
                return false;
            } else {
                frameQueue->push(nullptr);
                qWarning() << "Error avcodec_receive_frame:" << ffmpegErrToString(ret);
                return false;
            }
        }
        return false;
    }

    YT20_THREAD_SAFE VideoFrameRef getPicture() override { NOT_IMPLEMENT_YET }

    YT20_THREAD_SAFE AudioFrame getSample() override { NOT_IMPLEMENT_YET }

    YT20AudioFormat getInputFormat() override { NOT_IMPLEMENT_YET }

    void setOutputFormat(const YT20AudioFormat &format) override { NOT_IMPLEMENT_YET }


    YT20_THREAD_SAFE qreal viewFront() override {
        return frameQueue->viewFront<qreal>([this](AVFrame * frame) {
            if (frame) {
                return static_cast<qreal>(frame->pts) * av_q2d(stream->time_base);
            } else {
                return std::numeric_limits<qreal>::quiet_NaN();
            }
        });
    }

    YT20_THREAD_SAFE int skip(const std::function<bool(qreal)> &predicate) override {
        return frameQueue->skip([this, predicate](AVFrame *frame){
            return frame && predicate(static_cast<qreal>(frame->pts) * av_q2d(stream->time_base));
        }, [](AVFrame *frame) { av_frame_free(&frame); });
    }

    YT20_THREAD_SAFE void setEnable(bool b) override {
        frameQueue->setEnable(b);
    }

    YT20_GUARD_BY(DECODER) void flushFFmpegBuffers() override {
        avcodec_flush_buffers(codecCtx);
    }

};

/**
 * 音频解码器实现
 */
template<> class DecoderImpl<Audio>: public DecoderImpl<Common> {
    SwrContext *swrCtx = nullptr;
    uint8_t *audioOutBuf = nullptr;
    AVFrame * sampleFrameBuf = nullptr;
    YT20AudioFormat targetFmt = YT20AudioFormat(YT20Player::Int16, 44100, 2);

public:
    DecoderImpl(AVStream *vs, TwinsBlockQueue<AVFrame *> *queue) : DecoderImpl<Common>(vs, queue) {
        if (!(audioOutBuf = static_cast<uint8_t *>(av_malloc(2 * MAX_AUDIO_FRAME_SIZE)))) {
            throw std::runtime_error("Cannot alloc audioOutBuf");
        }
        sampleFrameBuf = av_frame_alloc();
    }

    virtual ~DecoderImpl() override {
        if (sampleFrameBuf) { av_frame_free(&sampleFrameBuf); }
        if (audioOutBuf) { av_freep(&audioOutBuf); }
        if (swrCtx) { swr_free(&swrCtx); }
    }


    YT20_THREAD_SAFE AudioFrame getSample() override {
        if (!frameQueue->isEnable()) {
            ILLEGAL_STATE("forward: getSample is disabled");
        }

        AVFrame *frame = frameQueue->remove(true);
        if (!frame) { return {}; }
        double pts = static_cast<double>(frame->pts) * av_q2d(stream->time_base);
        int len = swr_convert(swrCtx, &audioOutBuf, 2 * MAX_AUDIO_FRAME_SIZE,
                              const_cast<const uint8_t **>(frame->data), frame->nb_samples);

        int out_size = av_samples_get_buffer_size(nullptr, targetFmt.getChannelCount(),
                                                  len,
                                                  targetFmt.getSampleFormatForFFmpeg(),
                                                  1);
        av_frame_free(&frame);
        return {reinterpret_cast<std::byte *>(audioOutBuf), out_size, pts};
    }

    YT20AudioFormat getInputFormat() override {
        return {YT20Player::valueOf(codecCtx->sample_fmt), codecCtx->sample_rate, codecCtx->channels};
    }

    void setOutputFormat(const YT20AudioFormat& format) override {
        targetFmt = format;
        if (swrCtx) { swr_free(&swrCtx); }
        this->swrCtx = swr_alloc_set_opts(swrCtx, av_get_default_channel_layout(format.getChannelCount()),
                                          format.getSampleFormatForFFmpeg(), format.getSampleRate(),
                                          static_cast<int64_t>(codecCtx->channel_layout), codecCtx->sample_fmt,
                                          codecCtx->sample_rate, 0, nullptr);

        if (!swrCtx || swr_init(swrCtx) < 0) {
            throw std::runtime_error("Cannot initialize swrCtx");
        }
    }

};

/**
 * 视频解码器实现
 */
template<> class DecoderImpl<Video>: public DecoderImpl<Common> {
private:
    /**
     * 如果视频的第一帧 pts < 0, 则说明第一帧为封面. 保存下来.
     */
    std::atomic<AVFrame *> stillVideoFrame = nullptr;
public:
    DecoderImpl(AVStream *vs, TwinsBlockQueue<AVFrame *> *queue) : DecoderImpl<Common>(vs, queue) {}


    VideoFrameRef getPicture() override {
        if (stillVideoFrame != nullptr) {
            // qDebug() << "stillVideoFrame is available: " <<  static_cast<void *>(stillVideoFrame);
            return {stillVideoFrame, true, -1};
        }
        AVFrame *frame = frameQueue->remove(true);
        // qDebug() << "stillVideoFrame is not available,get pic from decoder: " << static_cast<void *>(frame) << "format: " << frame->format;
        if (!frame) { return {}; }
        if (frame->pts < 0) {
            stillVideoFrame = frame;
            return {frame, true, -9};
        } else {double pts = static_cast<double>(frame->pts) * av_q2d(stream->time_base);
            return {frame, true, pts};
        }

        // double pts = static_cast<double>(frame->pts) * av_q2d(stream->time_base);
        // return {frame, true, pts};
    }


    ~DecoderImpl() override {
        auto *frame = stillVideoFrame.load();
        if (frame) { av_frame_free(&frame); }
    }


};



#endif // FORWARD_H
