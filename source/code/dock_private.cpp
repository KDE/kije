/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "dock_private.h"

QQuickItem* DockPrivate::rootItem(QQuickItem *item)
{
    auto parent = item;
    QQuickItem *ret = item;
    while (parent != nullptr) {
        ret = parent;
        parent = parent->parentItem();
    }
    return ret;
}

bool DockPrivate::locked()
{
    return m_semaphore > 0;
}

void DockPrivate::semaphoreUp()
{
    m_semaphore++;
    Q_EMIT lockedChanged();
}

void DockPrivate::semaphoreDown()
{
    m_semaphore--;
    Q_EMIT lockedChanged();
}