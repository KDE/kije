/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include <QQmlEngine>

#include "dock_private.h"
#include "toolbar_private.h"

#include "kije_plugin.h"

#define PUBLIC_URI "org.kde.kije"
#define PRIVATE_URI "org.kde.kije.private"

#define URI(x) fromBase(QStringLiteral(x))

void KijePlugin::registerTypes(const char * uri) {
    qmlRegisterType(URI("controls/toolbar/ToolBar.qml"), PUBLIC_URI, 1, 0, "ToolBar");
    qmlRegisterType(URI("controls/action/Action.qml"), PUBLIC_URI, 1, 0, "Action");
    qmlRegisterType(URI("controls/applicationwindow/ApplicationWindow.qml"), PUBLIC_URI, 1, 0, "ApplicationWindow");
    qmlRegisterType(URI("controls/welcome/WelcomeScreen.qml"), PUBLIC_URI, 1, 0, "WelcomeScreen");
    qmlRegisterType(URI("controls/welcome/WelcomeSection.qml"), PUBLIC_URI, 1, 0, "WelcomeSection");
    qmlRegisterType(URI("controls/welcome/WelcomeItem.qml"), PUBLIC_URI, 1, 0, "WelcomeItem");
    qmlRegisterType(URI("controls/dock/DockItem.qml"), PUBLIC_URI, 1, 0, "DockItem");
    qmlRegisterSingletonType<ToolbarPrivate>(PRIVATE_URI, 1, 0, "ToolbarPrivate", [](QQmlEngine*, QJSEngine*) { return new ToolbarPrivate; });
    qmlRegisterSingletonType<DockPrivate>(PRIVATE_URI, 1, 0, "DockPrivate", [](QQmlEngine*, QJSEngine*) { return new DockPrivate; });
}
