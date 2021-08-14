/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "kije_page_p.h"

KijePage::KijePage(QQuickItem* parent) : QQuickItem(parent), d(new Private)
{

}

KijePage::~KijePage()
{

}

QStringList KijePage::actions() const
{
    return d->actions;
}

void KijePage::setActions(const QStringList& actions)
{
    if (d->actions == actions) {
        return;
    }

    d->actions = std::move(actions);
    Q_EMIT actionsChanged();
}
