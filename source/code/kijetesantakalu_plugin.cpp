#include <QQmlEngine>

#include "toolbar_private.h"

#include "kijetesantakalu_plugin.h"

#define PUBLIC_URI "org.kde.kijetesantakalu"
#define PRIVATE_URI "org.kde.kijetesantakalu.private"

#define URI(x) fromBase(QStringLiteral(x))

void KijetesantakaluPlugin::registerTypes(const char * uri) {
    qmlRegisterType(URI("controls/ToolBar.qml"), PUBLIC_URI, 1, 0, "ToolBar");
    qmlRegisterSingletonType<ToolbarPrivate>(PRIVATE_URI, 1, 0, "ToolbarPrivate", [](QQmlEngine*, QJSEngine*) { return new ToolbarPrivate; });
}
