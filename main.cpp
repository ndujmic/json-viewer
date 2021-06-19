#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDebug>
#include <QQmlContext>
#include "buttonhandler.h"
#include "jsonhandler.h"
#include "jsonhighlighter.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QIODevice>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);
    QQuickView view;

//    view.engine();
    JsonHandler jsonHandler;
    view.engine()->rootContext()->setContextProperty("jsonHandler", &jsonHandler);
    qmlRegisterType<JsonHandler>("com.company.json", 1, 0, "JsonHandler");

    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}


