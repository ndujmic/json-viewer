#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDebug>
#include <QQmlContext>
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
    QQuickView view;

    JsonHandler jsonHandler;
    view.engine()->rootContext()->setContextProperty("jsonHandler", &jsonHandler);

    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}


