#ifndef AUDIOFORMAT_H
#define AUDIOFORMAT_H

#include <QtCore>
#include <utility>
#include "portaudio.h"

extern "C" {
#include "libavutil/samplefmt.h"
}



struct AudioDataInfo {
    qint32 origLength;
    qint32 processedLength;
    qreal speedUpRate;
};

struct YT20SampleFormat {
private:
    using TransformFunc = std::function<void(std::byte *, qreal, unsigned long)>;

    int m_index;
    PaSampleFormat m_paSampleFormat;
    AVSampleFormat m_ffmpegSampleFormat;
    int m_bytesPerSample;
    std::function<void(std::byte *, qreal, unsigned long)> m_transform;

public:
    YT20SampleFormat(
        int mIndex,
        PaSampleFormat paSampleFormat,
        AVSampleFormat ffmpegSampleFormat,
        int bytesPerSample,
        TransformFunc transformFunc
        ) : m_index(mIndex),
        m_paSampleFormat(paSampleFormat),
        m_ffmpegSampleFormat(ffmpegSampleFormat),
        m_bytesPerSample(bytesPerSample),
        m_transform(std::move(transformFunc)) {}

    YT20SampleFormat& operator=(const YT20SampleFormat& other) {
        if (this != &other) {
            m_index = other.m_index;
            m_paSampleFormat = other.m_paSampleFormat;
            m_ffmpegSampleFormat = other.m_ffmpegSampleFormat;
            m_bytesPerSample = other.m_bytesPerSample;
            m_transform = other.m_transform; // 拷贝函数对象
        }
        return *this;
    }

    YT20SampleFormat(const YT20SampleFormat& other)
        : m_index(other.m_index),
        m_paSampleFormat(other.m_paSampleFormat),
        m_ffmpegSampleFormat(other.m_ffmpegSampleFormat),
        m_bytesPerSample(other.m_bytesPerSample),
        m_transform(other.m_transform) {}

public:
    template<class T>
    static YT20SampleFormat of(PaSampleFormat paSample, AVSampleFormat ffmpegSample) noexcept {
        static int id = 0;
        TransformFunc transform;
        size_t size;
        if constexpr(std::is_same<T, void>()) {
            transform = [](std::byte *src_, qreal factor, unsigned long samples) {
                throw std::runtime_error("Unsupported samples format.");
            };
            size = 0xABCDEF;
        } else {
            transform = [](std::byte *src_, qreal factor, unsigned long samples) {
                T *src = static_cast<T *>(static_cast<void *>(src_));
                for (size_t sampleOffset = 0; sampleOffset < samples; sampleOffset++) {
                    src[sampleOffset] = static_cast<T>(src[sampleOffset] * factor);
                }
            };
            size = sizeof(T);
        }
        return {id, paSample, ffmpegSample, static_cast<int>(size), transform};
    }


    void transformSampleVolume(std::byte *src, qreal factor, unsigned long samples) const {
        m_transform(src, factor, samples);
    }

    bool operator==(const YT20SampleFormat &rhs) const {
        return this->m_index == rhs.m_index;
    }

    bool operator!=(const YT20SampleFormat &rhs) const {
        return !(rhs == *this);
    }

    [[nodiscard]] PaSampleFormat getPaSampleFormat() const {
        return m_paSampleFormat;
    }

    [[nodiscard]] AVSampleFormat getFFmpegSampleFormat() const {
        return m_ffmpegSampleFormat;
    }

    [[nodiscard]] int getBytesPerSample() const {
        return m_bytesPerSample;
    }

};



class YT20AudioFormat {
private:
    YT20SampleFormat m_sampleFormat;
    int m_sampleRate;
    int m_channelCount;

public:

    YT20AudioFormat(
        YT20SampleFormat sampleFormat,
        int sampleRate,
        int channelCount
        ) noexcept: m_sampleFormat(std::move(sampleFormat)), m_sampleRate(sampleRate), m_channelCount(channelCount) {}


    [[nodiscard]] const YT20SampleFormat &getSampleFormat() const { return m_sampleFormat; }

    [[nodiscard]] PaSampleFormat getSampleFormatForPA() const {
        return m_sampleFormat.getPaSampleFormat();
    }

    [[nodiscard]] AVSampleFormat getSampleFormatForFFmpeg() const {
        return m_sampleFormat.getFFmpegSampleFormat();
    }

    [[nodiscard]] qreal durationOfBytes(int64_t bytes) const {
        return static_cast<qreal>(bytes) / (m_sampleRate * m_channelCount * getBytesPerSample());
    }

    [[nodiscard]] int64_t bytesOfDuration(qreal duration) const {
        return static_cast<int64_t>(duration * m_sampleRate * m_channelCount * getBytesPerSample());
    }

    [[nodiscard]] int getBytesPerSample() const {
        return m_sampleFormat.getBytesPerSample();
    }

    [[nodiscard]] int getBytesPerSampleChannels() const {
        return m_sampleFormat.getBytesPerSample() * m_channelCount;
    }

    [[nodiscard]] int getSampleRate() const {
        return m_sampleRate;
    }

    [[nodiscard]] int getChannelCount() const {
        return m_channelCount;
    }

    [[nodiscard]] int64_t suggestedRingBuffer(qreal speedFactor) const {
        return qBound<int64_t>(
            static_cast<int64_t>(2 * 1024 * m_channelCount * m_sampleFormat.getBytesPerSample()),
            bytesOfDuration(0.2 * speedFactor),
            256 << 20
            );
    }
};

namespace YT20Player {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
const YT20SampleFormat Unknown = YT20SampleFormat::of<void>(paNonInterleaved, AV_SAMPLE_FMT_NONE);
const YT20SampleFormat UInt8 = YT20SampleFormat::of<uint8_t>(paUInt8, AV_SAMPLE_FMT_U8);
const YT20SampleFormat Int16 = YT20SampleFormat::of<int16_t>(paInt16, AV_SAMPLE_FMT_S16);
const YT20SampleFormat Int32 = YT20SampleFormat::of<int32_t>(paInt32, AV_SAMPLE_FMT_S32);
const YT20SampleFormat Float = YT20SampleFormat::of<float_t>(paFloat32, AV_SAMPLE_FMT_FLT);
#pragma GCC diagnostic pop
const YT20AudioFormat DEFAULT_AUDIO_FORMAT = {Int16, 44100, 2};

static YT20SampleFormat valueOf(AVSampleFormat ffmpegFormat) {
    switch (ffmpegFormat) {
    case AV_SAMPLE_FMT_U8:
    case AV_SAMPLE_FMT_U8P:
        return UInt8;
    case AV_SAMPLE_FMT_S16:
    case AV_SAMPLE_FMT_S16P:
        return Int16;
    case AV_SAMPLE_FMT_S32:
    case AV_SAMPLE_FMT_S32P:
        return Int32;
    case AV_SAMPLE_FMT_FLT:
    case AV_SAMPLE_FMT_FLTP:
        return Float;
    default:
        return Unknown;
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
static YT20SampleFormat valueOf(PaSampleFormat paSampleFormat) {
    switch (paSampleFormat) {
    case paUInt8:
        return UInt8;
    case paInt16:
        return Int16;
    case paInt32:
        return Int32;
    case paFloat32:
        return Float;
    default:
        return Unknown;
    }

}
#pragma GCC diagnostic pop
}


#endif // AUDIOFORMAT_H
