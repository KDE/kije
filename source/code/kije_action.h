/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QObject>

class KijeAction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)

    struct Private;
    QScopedPointer<Private> d;

public:

    explicit KijeAction(QObject* parent = nullptr);
    ~KijeAction();

    QString identifier() const;
    void setIdentifier(const QString& identifier);
    Q_SIGNAL void identifierChanged();
};