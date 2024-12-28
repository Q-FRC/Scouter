#include "PlatformHelper.h"

PlatformHelper::PlatformHelper(QObject *parent)
    : QObject{parent}
{}

bool PlatformHelper::isAndroid()
{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

bool PlatformHelper::isWeb()
{
#ifdef Q_OS_WASM
    return true;
#else
    return false;
#endif

}
