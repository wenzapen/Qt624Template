#ifndef FRAME_H
#define FRAME_H

#include "helper.h"
#include "yt20player.h"
#include <mutex>
#include <functional>
#include <queue>
extern "C" {
#include <libavformat/avformat.h>
}

    typedef std::function<void(AVFrame *)> FrameFreeFunc;

class VideoFrame {
public:
    AVFrame *m_frame;
    std::atomic<int> m_refCount;
    const double m_pts;
    const bool m_isValid;

    friend class VideoFrameRef;
public:
    static inline std::atomic<int> totalCount = 0;

    VideoFrame(AVFrame *frame, double pts, const bool isValid)
        : m_frame(frame), m_refCount(1), m_pts(pts), m_isValid(isValid) {
        if (frame) ++totalCount;
    }

    ~VideoFrame() {
        if (m_frame) {
            --totalCount;
            // qDebug() << "deconstructor VideoFrame : " << static_cast<void*>(m_frame);
            av_frame_free(&m_frame);
            // av_frame_unref(m_frame);

        }
    }

    void unref() {
        if (--m_refCount == 0) {
            delete this;
        }
    }

    AVFrame* getAVFrame() const {
        return m_frame;
    }
};

class VideoFrameRef {
public:
    VideoFrame *m_videoFrame;
public:
    VideoFrameRef(AVFrame *frame, bool isValid, double pts) {
        m_videoFrame = new VideoFrame(frame, pts, isValid);
    }

    VideoFrameRef() : VideoFrameRef(nullptr, false, std::numeric_limits<double>::quiet_NaN()) {}

    VideoFrameRef(VideoFrameRef &&rhs) noexcept: m_videoFrame(rhs.m_videoFrame) {
        rhs.m_videoFrame = nullptr;
    }

    VideoFrameRef(const VideoFrameRef &rhs) : m_videoFrame(rhs.m_videoFrame) {
        ++rhs.m_videoFrame->m_refCount;
    }

    VideoFrameRef &operator=(VideoFrameRef &&rhs) noexcept {
        if (this->m_videoFrame) { this->m_videoFrame->unref(); }
        this->m_videoFrame = rhs.m_videoFrame;
        rhs.m_videoFrame = nullptr;
        return *this;
    }

    VideoFrameRef &operator=(const VideoFrameRef &rhs) noexcept {
        if (&rhs != this) {
            if (this->m_videoFrame) { this->m_videoFrame->unref(); }
            this->m_videoFrame = rhs.m_videoFrame;
            ++m_videoFrame->m_refCount;
        }
        return *this;
    }


    ~VideoFrameRef() {
        if (m_videoFrame) { m_videoFrame->unref(); }
    }

    bool operator==(const VideoFrameRef &frame) const {
        return this->m_videoFrame == frame.m_videoFrame;
    }

    bool operator!=(const VideoFrameRef &frame) const {
        return !this->operator==(frame);
    }

    /**
     * @return 图像数据是否有效
     */
    [[nodiscard]] bool isValid() const {
        return m_videoFrame && m_videoFrame->m_isValid;
    }


    [[nodiscard]] double getPTS() const {
        return m_videoFrame->m_pts;
    }

    [[nodiscard]] std::byte *getY() const {
        return !m_videoFrame->m_frame ? nullptr : reinterpret_cast<std::byte *>(m_videoFrame->m_frame->data[0]);
    }

    [[nodiscard]] std::byte *getU() const {
        return !m_videoFrame->m_frame ? nullptr : reinterpret_cast<std::byte *>(m_videoFrame->m_frame->data[1]);
    }

    [[nodiscard]] std::byte *getV() const {
        return !m_videoFrame->m_frame ? nullptr : reinterpret_cast<std::byte *>(m_videoFrame->m_frame->data[2]);
    }

    [[nodiscard]] int getLineSize() const {
        return !m_videoFrame->m_frame ? 0 : m_videoFrame->m_frame->linesize[0];
    }

    [[nodiscard]] int getWidth() const {
        return !m_videoFrame->m_frame ? 0 : m_videoFrame->m_frame->width;
    }

    [[nodiscard]] int getHeight() const {
        return !m_videoFrame->m_frame ? 0 : m_videoFrame->m_frame->height;
    }

    [[nodiscard]] bool isSameSize(const VideoFrameRef &frame) const {
        return (this->isValid()
                && frame.isValid()
                && this->getWidth() == frame.getWidth()
                && this->getHeight() == frame.getHeight()
                && this->getLineSize() == frame.getLineSize())
               || (!this->isValid() && !frame.isValid());
    }

    [[nodiscard]] bool isSameSize(int width, int height) const {
        return this->isValid() && this->getWidth() == width && this->getHeight() == height;
    }

    [[nodiscard]] VideoFrame* getFrame() const {
        return m_videoFrame;
    }

};

class AudioFrame {
private:
    std::byte *m_data;
    int m_len;
    double m_pts;
public:
    AudioFrame() : m_data(nullptr), m_len(0), m_pts(std::numeric_limits<double>::quiet_NaN()) {}

    AudioFrame(std::byte *data, int len, double pts) : m_data(data), m_len(len), m_pts(pts) {}

    bool isValid() {
        return m_data;
    }

    [[nodiscard]] std::byte *getSampleData() const {
        return m_data;
    }

    [[nodiscard]] int getDataLen() const {
        return m_len;
    }

    [[nodiscard]] double getPTS() const {
        return m_pts;
    }
};



#endif // FRAME_H
