#ifndef VIRTUAL_H
#define VIRTUAL_H

//
// Created by ColorsWind on 2022/6/1.
//
#include <yt20player.h>

/**
 * @brief 虚拟视频播放, 用于视频纯音频文件.
 */
class VirtualVideoDecoder : public IDemuxDecoder {
private:
    qreal m_audioDuration;
public:
    VirtualVideoDecoder(qreal audioDuration) : m_audioDuration(audioDuration) {}

    YT20_THREAD_SAFE bool accept(AVPacket *pkt, std::atomic<bool> &interrupt) override {
        return !interrupt;
    }

    YT20_THREAD_SAFE void flushFFmpegBuffers() override {}

    YT20_THREAD_SAFE VideoFrameRef getPicture() override {
        return {nullptr, true, std::numeric_limits<qreal>::quiet_NaN()};
    }

    YT20_THREAD_SAFE AudioFrame getSample() override {
        NOT_IMPLEMENT_YET
    }

    YT20_THREAD_SAFE double duration() override {
        return m_audioDuration;
    }

    YT20_THREAD_SAFE qreal viewFront() override {
        return std::numeric_limits<qreal>::quiet_NaN();
    }

    YT20_THREAD_SAFE int skip(const std::function<bool(qreal)> &predicate) override {
        return 0;
    }

    YT20_THREAD_SAFE void setEnable(bool b) override {}

    YT20_THREAD_SAFE YT20AudioFormat getInputFormat() override { NOT_IMPLEMENT_YET }

    YT20_THREAD_SAFE void setOutputFormat(const YT20AudioFormat &format) override { NOT_IMPLEMENT_YET }

};


#endif // VIRTUAL_H
