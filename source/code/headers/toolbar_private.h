/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QObject>
#include <QQuickItem>

class ToolbarPrivate : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE int calculateDragIndex(QQuickItem *rowLayout, QQuickItem *draggee, qreal currentDragX);
    Q_INVOKABLE QVariantList recallToolbar(const QString &id);
    Q_INVOKABLE void serializeToolbar(const QString &id, QQmlListReference data);
    Q_INVOKABLE void forgetToolbar(const QString &id);
};