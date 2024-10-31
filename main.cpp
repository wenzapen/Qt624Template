#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <hurricane.h>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    qmlRegisterType<Hurricane>("HurricanePlayer", 1, 0, "HurricanePlayer");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Qt624Template/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
