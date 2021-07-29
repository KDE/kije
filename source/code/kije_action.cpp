/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "kije_action.h"

struct KijeAction::Private
{
    QString identifier;
};

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
