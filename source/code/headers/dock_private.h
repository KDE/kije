/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QObject>
#include <QQuickItem>

class DockPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool locked READ locked NOTIFY lockedChanged)
public:
    Q_INVOKABLE QQuickItem* rootItem(QQuickItem *item);
    bool locked();
    Q_SIGNAL void lockedChanged();
    Q_INVOKABLE void semaphoreUp();
    Q_INVOKABLE void semaphoreDown();
private:
    int m_semaphore;
};