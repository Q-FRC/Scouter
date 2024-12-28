#ifndef PLATFORMHELPER_H
#define PLATFORMHELPER_H

#include <QObject>

class PlatformHelper : public QObject
{
    Q_OBJECT
public:
    explicit PlatformHelper(QObject *parent = nullptr);

    Q_INVOKABLE bool isAndroid();
    Q_INVOKABLE bool isWeb();

signals:
};

#endif // PLATFORMHELPER_H
