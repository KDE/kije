/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "kije_action.h"

#include "kije_app.h"

struct KijeAbstractApp::Private
{
    QList<KijeAction*> actions;
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

KijeAction* KijeAbstractApp::lookupAction(const QString &name) const
{
    for (auto action : d->actions) {
        if (action->identifier() == name) {
            return action;
        }
    }

    return nullptr;
}
