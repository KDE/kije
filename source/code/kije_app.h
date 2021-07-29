/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QObject>
#include <QQmlListProperty>

class KijeAction;

class KijeAbstractApp : public QObject
{
    Q_OBJECT

    struct Private;
    QScopedPointer<Private> d;

    static KijeAbstractApp* s_instance;

    Q_PROPERTY(QQmlListProperty<KijeAction> actions READ actions)

public:

    explicit KijeAbstractApp(QObject* parent = nullptr);
    ~KijeAbstractApp();

    static KijeAbstractApp* instance();

    QQmlListProperty<KijeAction> actions();

};

class KijeDocApp : public KijeAbstractApp
{

    Q_OBJECT

public:

    explicit KijeDocApp(QObject* parent = nullptr);
    ~KijeDocApp();

};

class KijeApp : public KijeAbstractApp
{

    Q_OBJECT

public:
    explicit KijeApp(QObject* parent = nullptr);
    ~KijeApp();

};