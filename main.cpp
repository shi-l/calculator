#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <calculator.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    calculator calculator;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Calculator",&calculator);
        const QUrl url(u"qrc:/calculator/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


    engine.load(url);
    return app.exec();
}
