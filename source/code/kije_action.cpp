/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "kije_action_p.h"

KijeAction::KijeAction(QObject* parent) : QObject(parent), d(new Private)
{

}

KijeAction::~KijeAction()
{

}

#define synthesize_set(name, signal) \
if (d->name == name) {\
    return;\
}\
d->name = name; \
Q_EMIT signal();

QString KijeAction::identifier() const
{
    return d->identifier;
}

void KijeAction::setIdentifier(const QString& identifier)
{
    synthesize_set(identifier, identifierChanged)
}

QString KijeAction::text() const
{
    return d->text;
}

void KijeAction::setText(const QString& text)
{
    synthesize_set(text, textChanged);
}

QQmlListProperty<KijeAction> KijeAction::childActions()
{
    return QQmlListProperty<KijeAction>{this, &d->actions};
}

const QList<KijeAction*> KijeAction::cxxChildActions()
{
    return d->actions;
}
