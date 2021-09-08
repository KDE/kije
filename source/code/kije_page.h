/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QQuickItem>

class KijePage : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QStringList actions READ actions WRITE setActions NOTIFY actionsChanged)

    struct Private;
    QScopedPointer<Private> d;

public:

    explicit KijePage(QQuickItem* parent = nullptr);
    ~KijePage();

    Q_SIGNAL void writeState(QJSValue state);
    Q_SIGNAL void restoreState(QJSValue state);

    QStringList actions() const;
    void setActions(const QStringList& actions);
    Q_SIGNAL void actionsChanged();

};