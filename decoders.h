#ifndef DECODERS_H
#define DECODERS_H

#include "helper.h"
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/error.h>
#include <libswresample/swresample.h>
#include <libavutil/imgutils.h>
#include <libavutil/hwcontext.h>
#include  <libavutil/timestamp.h>
}
#include <QDebug>
#include "frame.h"
#include "twinsqueue.h"
#include "concurrentqueue.h"
#include "audioformat.h"
#include <atomic>
#include <utility>
#include <iostream>

class IDemuxDecoder {

public:
    /**
     * 解码器类型
     */
    enum class DecoderType {
        Audio,  ///< 音频解码器
        Video,  ///< 视频解码器
        Common, ///< 未指定
    };
    /**
     * 接收一个包
     * @param pkt
     * @return 如果还需要接收下一个 packet 返回 true, 否则返回 false
     */
    virtual bool accept(AVPacket *pkt, std::atomic<bool> &interrupt) = 0;

    /**
     * 清空 FFmpeg 内部缓冲区
     */
    virtual void flushFFmpegBuffers() = 0;


    /**
     * 获取视频帧并从队列中删除, 仅当当前解码器是视频解码器时有效
     * @param b 是否阻塞
     * @return 视频帧, 请用 isValid 判断是否有效
     */
    virtual VideoFrameRef getPicture() = 0;

    /**
    * 获取音频帧并从队列中删除, 仅当当前解码器是音频解码器时有效
    * @param b 是否阻塞
    * @return 音频帧, 请用 isValid 判断是否有效
    */
    virtual AudioFrame getSample() = 0;

    /**
     * 获取队首帧的PTS, 若不存在, 返回NaN
     * @return 队首帧的PTS
     */
    virtual qreal viewFront() = 0;

    /**
     * 线性扫描移除满足条件的帧, 当发现帧不满足条件时, 结束扫描
     * @param predicate 条件
     * @return 移除帧的个数
     */
    virtual int skip(const std::function<bool(qreal)> &predicate) = 0;

    /**
     * 获取流的长度
     * @return
     */
    virtual double duration() = 0;


    virtual void setEnable(bool b) = 0;

    virtual ~IDemuxDecoder() = default;

    virtual void setFollower(IDemuxDecoder* follower) {NOT_IMPLEMENT_YET}

    virtual void pushFrameStack() {}

    virtual qreal getLastPts() {
        NOT_IMPLEMENT_YET
    }

    virtual void clearFrameStack() {}

    virtual void setStart(qreal secs) {}

    virtual qreal nextSegment() {
        NOT_IMPLEMENT_YET
    }

    virtual YT20AudioFormat getInputFormat() = 0;

    virtual void setOutputFormat(const YT20AudioFormat& format) = 0;
};

class DecoderContext {
public:
    AVCodec *codec = nullptr;
    AVStream *stream = nullptr;
    AVCodecContext *codecCtx = nullptr;
    AVFrame *frameBuf = nullptr;
    AVFrame *cpuFrame = nullptr;  // 用于存储从硬件转换后的CPU格式帧
    AVBufferRef *hw_device_ctx = nullptr;
    inline static enum AVPixelFormat hwPixFmt = AV_PIX_FMT_NONE;
    bool enableHwDecoder = true;

    DecoderContext(AVStream *vs): stream(vs) {
        auto *videoCodecPara = stream->codecpar;
        if (!(codec = const_cast<AVCodec *>(avcodec_find_decoder(videoCodecPara->codec_id)))) {
            throw std::runtime_error("Cannot find valid video decode codec.");
        }



        if (!(codecCtx = avcodec_alloc_context3(codec))) {
            throw std::runtime_error("Cannot find valid video decode codec context.");
        }


        if (avcodec_parameters_to_context(codecCtx, videoCodecPara) < 0) {
            throw std::runtime_error("Cannot initialize videoCodecCtx.");
        }

        // Step 2: Set up hardware acceleration
        if ( enableHwDecoder && !setupHardwareAcceleration(videoCodecPara->codec_id)) {
            std::cout << "Hardware acceleration not supported, using software decoding." << std::endl;
        }

        // codecCtx->reorder_pts = 1;
        codecCtx->pkt_timebase = stream->time_base;


        if (avcodec_open2(codecCtx, codec, nullptr) < 0) {
            throw std::runtime_error("Cannot open codec.");
        }
        if (!(frameBuf = av_frame_alloc()) || !(cpuFrame = av_frame_alloc())) {
            throw std::runtime_error("Cannot alloc frame buf.");
        }
    }

    ~DecoderContext() {
        if (frameBuf) { av_frame_free(&frameBuf); }
        if (cpuFrame) { av_frame_free(&cpuFrame); }
        if (codecCtx) { avcodec_close(codecCtx); }
        if (codecCtx) { avcodec_free_context(&codecCtx); }
        if (hw_device_ctx) { av_buffer_unref(&hw_device_ctx); }
    }

private:
    bool setupHardwareAcceleration(AVCodecID codec_id) {
        AVHWDeviceType deviceType = AV_HWDEVICE_TYPE_NONE;

        // Iterate through all available hardware devices
        while ((deviceType = av_hwdevice_iterate_types(deviceType)) != AV_HWDEVICE_TYPE_NONE) {
            qDebug() << "Checking for hardware decoding support:" << av_hwdevice_get_type_name(deviceType);

            for (int i = 0;; i++) {
                const AVCodecHWConfig *config = avcodec_get_hw_config(codec, i);
                if (!config) {
                    qDebug() << QString("Decoder %1 does not support device type %2.")
                    .arg(codec->name)
                        .arg(av_hwdevice_get_type_name(deviceType));
                    return false;
                }
                if (config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX &&
                    config->device_type == deviceType) {
                    hwPixFmt = config->pix_fmt;
                    break;
                }
            }

            if (av_hwdevice_ctx_create(&hw_device_ctx, deviceType, nullptr, nullptr, 0) == 0) {
                codecCtx->get_format = get_hw_format;
                codecCtx->hw_device_ctx = av_buffer_ref(hw_device_ctx);

                qDebug() << "Using hardware acceleration:" << av_hwdevice_get_type_name(deviceType);
                return true;
            } else {
                qDebug() << "Failed to initialize" << av_hwdevice_get_type_name(deviceType) << "device context.";
            }
        }

        qDebug() << "No supported hardware acceleration found, defaulting to software decoding.";
        return false;
    }

    static enum AVPixelFormat get_hw_format(AVCodecContext *ctx, const enum AVPixelFormat *pix_fmts) {
        const enum AVPixelFormat *p;

        for (p = pix_fmts; *p != -1; p++) {
            if (*p == hwPixFmt)
                return *p;
        }

        qDebug("Failed to get HW surface format.\n");
        return AV_PIX_FMT_NONE;
    }

};

// AVPixelFormat DecoderContext::hwPixFmt = AV_PIX_FMT_NONE;
constexpr auto Audio  =  IDemuxDecoder::DecoderType::Audio;
constexpr auto Video  =  IDemuxDecoder::DecoderType::Video;
constexpr auto Common =  IDemuxDecoder::DecoderType::Common;



#endif // DECODERS_H
