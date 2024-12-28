#include "BuildConfig.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QScreen>
#include <QZXing.h>

#include "Config.h"
#include "MatchData.h"
#include "PlatformHelper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

#ifdef Q_OS_ANDROID
    qputenv("QT_SCALE_FACTOR", QByteArray::number(0.5));
#else
    QSize screenSize = app.primaryScreen()->size();
    if (screenSize.width() < 1920 || screenSize.height() < 1080) {
        qputenv("QT_SCALE_FACTOR", QByteArray::number(screenSize.height() / 1080.0));
    }
#endif

    qputenv("QML_COMPAT_RESOLVE_URLS_ON_ASSIGNMENT", "1");
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "1");

    QZXing::registerQMLTypes();

    app.setOrganizationName(BuildConfig.ORG_NAME);
    app.setApplicationName(BuildConfig.APP_NAME);
    app.setApplicationVersion(BuildConfig.versionString());

    QQuickStyle::setStyle("Universal");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    QZXing::registerQMLImageProvider(engine);

    ScouterConfig *config = new ScouterConfig(&app);

    engine.rootContext()->setContextProperty("config", config);
    engine.rootContext()->setContextProperty("teleModel", config->teleModel());
    engine.rootContext()->setContextProperty("autoModel", config->autoModel());
    engine.rootContext()->setContextProperty("endModel", config->endModel());
    engine.rootContext()->setContextProperty("scalesModel", config->scalesModel());

    MatchData *match = new MatchData(&app);

    engine.rootContext()->setContextProperty("matchData", match);

    PlatformHelper *platform = new PlatformHelper(&app);

    engine.rootContext()->setContextProperty("platform", platform);

    engine.loadFromModule("QFRCScouter", "Main");

    return app.exec();
}
