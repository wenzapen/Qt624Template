#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <hurricane.h>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    qmlRegisterType<Hurricane>("HurricanePlayer", 1, 0, "HurricanePlayer");


    qmlRegisterUncreatableMetaObject(
        YT20Player::staticMetaObject, // meta object created by Q_NAMESPACE macro
        "yt20player.ns",                // import statement (can be any string)
        1, 0,                          // major and minor version of the import
        "YT20PlayerNS",                 // name in QML (does not have to match C++ name)
        "Error: only enums"            // error in case someone tries to create a MyNamespace object
        );

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Qt624Template/main.qml"));
    // const QUrl url(QStringLiteral("qrc:/Qt624Template/hardwareVideoPlayer.qml"));
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
