#include <QApplication >
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include "mywidget.h"
#include "mywidgetwrapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication  app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<CMyWidgetWrapper>("MyWidgetWrapper", 1, 0, "CMyWidgetWrapper");

    CMyWidget *pwdgt = new CMyWidget();
    CMyWidgetWrapper wrapper;
    wrapper.SetWidget(pwdgt);
    engine.rootContext()->setContextProperty("wrapper", &wrapper);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

//    QQuickWidget *qmlWidget = new QQuickWidget(QUrl("qrc:/main.qml"));
//    qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
//    qmlWidget->resize(800, 600);
//    qmlWidget->show();

////    CMyWidget *pwdgt = new CMyWidget(qmlWidget);
////    pwdgt->resize(10,20);
////    pwdgt->show();

    return app.exec();
}
