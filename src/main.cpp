#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include "component/CircularReveal.h"
#include "component/controller.h"
#include "component/clipboard.h"
int main(int argc, char *argv[])
{
    const char *uri = "seccompjail";
    int major = 1;
    int minor = 0;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<CircularReveal>(uri, major, minor, "CircularReveal");
    qmlRegisterType<Controller>("Controller", 1, 0, "Controller");
    qmlRegisterType<ClipBoard>("ClipBoard", 1, 0, "ClipBoard");
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "seccomp-jail_" + QLocale(locale).name();
        if (translator.load("./i18n/"+ baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/App.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
