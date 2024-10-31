#ifndef FIREWORKS_H
#define FIREWORKS_H

#include <QQuickItem>
#include <QObject>
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include "renderer.h"
#include "platform.h"
#include <optional>


#include <QImage>
extern "C" {
#include <libswscale/swscale.h>
#include <libavutil/pixfmt.h>
}

struct YT20RenderSettings
{
    // For memory visibility, sync when both GUI and render threads are blocked.
    // We have to YT20RenderSettings, one can be modified on GUI thread (e.g. by QML),
    // and the other will be synchronized in SYNC stage.
    UpdateValueVideoFrameRef videoFrame;

};

// 将 VideoFrameRef 转换为 QImage，支持多种像素格式
inline QImage videoFrameRefToQImage(VideoFrameRef &videoFrameRef) {
    if (!videoFrameRef.isValid()) {
        return QImage(); // 返回无效 QImage
    }

    int width = videoFrameRef.getWidth();
    int height = videoFrameRef.getHeight();
    const AVFrame *frame = static_cast<const AVFrame*>(videoFrameRef.getFrame()->getAVFrame());

    // 创建 QImage (RGB888 格式)
    QImage image(width, height, QImage::Format_RGB888);

    // 创建 libswscale 的转换上下文
    SwsContext *swsContext = sws_getContext(
        width, height,
        static_cast<AVPixelFormat>(frame->format), // 输入帧格式
        width, height,
        AV_PIX_FMT_RGB24, // 输出格式为 RGB24
        SWS_BILINEAR,     // 缩放算法（这里选择双线性）
        nullptr, nullptr, nullptr);

    if (!swsContext) {
        qWarning("Failed to create SwsContext for frame conversion");
        return QImage();
    }

    // 设置目标数据指针（RGB 格式）
    uint8_t *dest[4] = { image.bits(), nullptr, nullptr, nullptr };
    int destStride[4] = { 3 * width, 0, 0, 0 }; // RGB888 每行 3 字节

    // 执行格式转换
    sws_scale(swsContext,
              frame->data,    // 输入图像数据
              frame->linesize, // 输入图像步长
              0, height,
              dest, destStride);

    // 释放转换上下文
    sws_freeContext(swsContext);

    return image;
}


class Fireworks : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool keepFrameRate READ isKeepFrameRate WRITE setKeepFrameRate NOTIFY keepFrameRateChanged)
    Q_PROPERTY(int frameHeight READ getHeight NOTIFY frameSizeChanged)
    Q_PROPERTY(int frameWidth READ getWidth NOTIFY frameSizeChanged)
    Q_PROPERTY(double frameRate READ getFrameRate NOTIFY frameSizeChanged)
    Q_PROPERTY(GLfloat brightness READ getBrightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(GLfloat contrast READ getContrast WRITE setContrast NOTIFY contrastChanged)
    Q_PROPERTY(GLfloat saturation READ getSaturation WRITE setSaturation NOTIFY saturationChanged)
    Q_PROPERTY(QString filterPrefix READ getFilterPrefix)
    Q_PROPERTY(QStringList filterJsons READ getFilterJsons)
private:
    FireworksRenderer *m_renderer;
    QString m_filterPrefix;
    QStringList m_filterJsons;
    int m_frameHeight = 1;
    int m_frameWidth = 1;
    double m_frameRate = 1.0;
    VideoFrameRef frame;
    bool firstImage = true;
protected:
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *data) override {
        qDebug("fireworks: updatePaintNode: triggered");
        QSGSimpleTextureNode *textureNode = static_cast<QSGSimpleTextureNode *>(node);
        if (!textureNode) {
            textureNode = new QSGSimpleTextureNode();
        }

        // FFmpeg 解码后的图像数据转换为 QImage
        QImage frameImage;
        if (firstImage) {
            frameImage = QImage("test1.jpg");   // 假设 getDecodedFrame() 返回解码后的帧
            firstImage = !firstImage;

        } else {
            frameImage = QImage("test1.jpeg");   // 假设 getDecodedFrame() 返回解码后的帧
            firstImage = !firstImage;
        }
        // QImage frameImage("test1.jpg");   // 假设 getDecodedFrame() 返回解码后的帧
        // QImage frameImage = videoFrameRefToQImage(frame);

        // 创建纹理
        QSGTexture *texture = window()->createTextureFromImage(frameImage);
        textureNode->setTexture(texture);
        // textureNode->setRect(boundingRect()); // 设置显示区域
        // 设置显示区域，使用帧的尺寸
        textureNode->setRect(0, 0, frameImage.width(), frameImage.height());

        return textureNode;

        // return m_renderer;
    }

public:
    explicit Fireworks(QQuickItem *parent = nullptr): QQuickItem(parent), m_renderer(new FireworksRenderer),
        m_filterPrefix(YT20Player::getAssetsDir() + u"/filters"_qs), m_filterJsons()  {
        QDir filterDir(m_filterPrefix);
        for(auto && filename : filterDir.entryList({"*.json"})) {
            QFile file = filterDir.filePath(filename);
            file.open(QIODevice::OpenModeFlag::ReadOnly);
            m_filterJsons.append(file.readAll());
            file.close();
        }
        this->setFlag(QQuickItem::ItemHasContents);
        connect(this, &QQuickItem::windowChanged, this, [this](QQuickWindow *win){
            qDebug() << "Window Size Changed:" << static_cast<void *>(win) << ".";
            if (win) {
                // connect(this->window(), &QQuickWindow::beforeSynchronizing, m_renderer, &FireworksRenderer::sync, Qt::DirectConnection);
                // connect(this->window(), &QQuickWindow::beforeRendering, m_renderer, &FireworksRenderer::init, Qt::DirectConnection);
                win->setColor(Qt::black);
            } else {
                qWarning() << "Window destroy.";
            }

        });
        qDebug() << "Create Hurricane QuickItem.";
    }
    ~Fireworks() override {
        m_renderer = nullptr;
    }

    YT20_GUARD_BY(MAIN) private:
              [[nodiscard]] QString getFilterPrefix() const { return m_filterPrefix; }

    [[nodiscard]] bool isKeepFrameRate() const { return m_renderer->isKeepFrameRate(); }

    [[nodiscard]] QStringList getFilterJsons() const { return m_filterJsons; }

    [[nodiscard]] GLfloat getBrightness() const { return m_renderer->getBrightness(); }

    void setKeepFrameRate(bool keep) {
        m_renderer->setKeepFrameRate(keep);
        emit keepFrameRateChanged();
    }

    void setBrightness(GLfloat b) {
        m_renderer->setBrightness(b);
        emit brightnessChanged();
    }

    [[nodiscard]] GLfloat getContrast() const {
        return m_renderer->getContrast();
    }

    void setContrast(GLfloat c) {
        m_renderer->setContrast(c);
        emit contrastChanged();
    };

    [[nodiscard]] GLfloat getSaturation() const { return m_renderer->getSaturation(); };

    void setSaturation(GLfloat s) {
        m_renderer->setSaturation(s);
        emit saturationChanged();
    };

    [[nodiscard]] int getHeight() const {
        return m_frameHeight;
    }

    [[nodiscard]] int getWidth() const {
        return m_frameWidth;
    }

    [[nodiscard]] double getFrameRate() const {
        return m_frameRate;
    }


public slots:

    void setVideoFrame(const VideoFrameRef &pic) {
        // this function must be called on GUI thread
        // setImage -> sync -> render
        // since picture may use on renderer thread, we CANNOT free now
        // no change, return immediately
        // if (m_renderer->setVideoFrame(pic)) {
        //     // make dirty
        //     this->update();
        //     if (!pic.isSameSize(m_frameWidth, m_frameHeight)) {
        //         m_frameWidth = pic.getWidth();
        //         m_frameHeight = pic.getHeight();
        //         m_frameRate = static_cast<double>(m_frameHeight) / static_cast<double>(m_frameWidth);
        //         emit frameSizeChanged();
        //     }
        // }
        if (frame == pic)
        {
            // return false;
            qDebug("fireworks: setVideoFrame: received a same frame");
            return;
        }
        {
            frame = pic;
            qDebug("fireworks: setVideoFrame: received a new frame");
            // return true;
        }
        this->update();
        if (!pic.isSameSize(m_frameWidth, m_frameHeight)) {
            m_frameWidth = pic.getWidth();
            m_frameHeight = pic.getHeight();
            m_frameRate = static_cast<double>(m_frameHeight) / static_cast<double>(m_frameWidth);
            emit frameSizeChanged();
        }
    }

    /**
     * 设置LUT滤镜路径
     * @param path
     */
    Q_INVOKABLE void setLUTFilter(const QString& path) {
        QImage image;
        if (!path.isEmpty()) {
            image.load(QDir(m_filterPrefix).filePath(path));
            image.convertTo(QImage::Format_RGB888);
        }

        m_renderer->setLUTFilter(image);
    }



signals:
    void brightnessChanged();

    void contrastChanged();

    void saturationChanged();

    void frameSizeChanged();

    void keepFrameRateChanged();
};







#endif // FIREWORKS_H