#pragma once

#include <QDir>
#include <QQmlExtensionPlugin>

class KijePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri) override;
private:
    QUrl fromBase(QString url) {
        return QDir::cleanPath(baseUrl().toString()+QDir::separator()+url);
    };
};