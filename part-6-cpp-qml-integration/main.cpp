#include "rover.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    Rover rover;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("rover", &rover);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](const QObject* obj, const QUrl& objUrl) {
            if (obj == nullptr && url == objUrl)
                QCoreApplication::exit(10);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
