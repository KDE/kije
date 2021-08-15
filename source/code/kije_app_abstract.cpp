/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "kije_action.h"
#include "kije_action_p.h"

#include "kije_app.h"

#include <QtGui/private/qguiapplication_p.h>
#include <QtGui/qpa/qplatformmenu.h>
#include <QtGui/qpa/qplatformtheme.h>

#include <QDebug>

struct KijeAbstractApp::Private
{
    QList<KijeAction*> actions;
    QList<KijeAction*> menubar;
};

KijeAbstractApp* KijeAbstractApp::s_instance = nullptr;

KijeAbstractApp::KijeAbstractApp(QObject* parent) : QObject(parent), d(new Private)
{
    if (s_instance) {
        qFatal("You cannot construct more than one instance of KijeApp!");
    }
    s_instance = this;
}

KijeAbstractApp::~KijeAbstractApp()
{
    s_instance = nullptr;
}

KijeAbstractApp* KijeAbstractApp::instance()
{
    return s_instance;
}

QQmlListProperty<KijeAction> KijeAbstractApp::actions()
{
    return QQmlListProperty<KijeAction>{this, &d->actions};
}

QQmlListProperty<KijeAction> KijeAbstractApp::menubar()
{
    return QQmlListProperty<KijeAction>{this, &d->menubar};
}

KijeAction* KijeAbstractApp::lookupAction(const QString &name) const
{
    for (auto action : d->actions) {
        if (action->identifier() == name) {
            return action;
        }
    }

    return nullptr;
}

template<typename A, typename B, typename C, typename D, typename E>
void conn(A fromObject, B fromSignal, C fromGetter, D toObject, E setter)
{
    (toObject->*setter)((fromObject->*fromGetter)());
    QObject::connect(fromObject, fromSignal, fromObject, [fromObject, fromGetter, toObject, setter]() {
        (toObject->*setter)((fromObject->*fromGetter)());
    });
}

void KijeAction::intoPlatformMenu(QPlatformMenu* menu)
{
    conn(this, &KijeAction::textChanged, &KijeAction::text, menu, &QPlatformMenu::setText);

    for (auto item : d->actions) {
        if (item->d->actions.length() > 0) {
            auto m = menu->createSubMenu();
            item->intoPlatformMenu(m);

            auto it = item->intoPlatformMenuItem(menu);
            it->setMenu(m);

            menu->insertMenuItem(it, nullptr);
        } else {
            menu->insertMenuItem(item->intoPlatformMenuItem(menu), nullptr);
        }
    }
}

QPlatformMenuItem* KijeAction::intoPlatformMenuItem(QPlatformMenu* of)
{
    auto item = of->createMenuItem();

    conn(this, &KijeAction::textChanged, &KijeAction::text, item, &QPlatformMenuItem::setText);
    conn(this, &KijeAction::enabledChanged, &KijeAction::enabled, item, &QPlatformMenuItem::setEnabled);

    item->setShortcut(toSequence(shortcut()));
    QObject::connect(this, &KijeAction::shortcutChanged, item, [this, item]() {
        item->setShortcut(toSequence(shortcut()));
    });

    connect(item, &QPlatformMenuItem::activated, this, &KijeAction::triggered);

    return item;
}

void KijeAbstractApp::attachMenubar(QWindow* win)
{
    auto mb = QGuiApplicationPrivate::platformTheme()->createPlatformMenuBar();
    if (!mb) {
        return;
    }

    for (auto it : d->menubar) {
        auto menu = mb->createMenu();
        it->intoPlatformMenu(menu);
        mb->insertMenu(menu, nullptr);
    }

    mb->handleReparent(win);
}
