/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QObject>
#include <QQmlListProperty>
#include <QQmlParserStatus>

class KijeAction;
class QWindow;
class QQmlComponent;

class KijeAbstractApp : public QObject
{
    Q_OBJECT

    struct Private;
    QScopedPointer<Private> d;

    static KijeAbstractApp* s_instance;

    Q_PROPERTY(QQmlListProperty<KijeAction> actions READ actions)
    Q_PROPERTY(QQmlListProperty<KijeAction> menubar READ menubar)

public:

    explicit KijeAbstractApp(QObject* parent = nullptr);
    ~KijeAbstractApp();

    static KijeAbstractApp* instance();

    Q_INVOKABLE void attachMenubar(QWindow* win);

    QQmlListProperty<KijeAction> actions();
    QQmlListProperty<KijeAction> menubar();
    Q_INVOKABLE KijeAction* lookupAction(const QString& name) const;

};

class KijeDocApp : public KijeAbstractApp, public QQmlParserStatus
{

    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    struct Private;
    QScopedPointer<Private> d;

    Q_PROPERTY(QQmlComponent* viewDelegate READ viewDelegate WRITE setViewDelegate NOTIFY viewDelegateChanged)

private:

    void newWindow(const QString& ident);
    void firstLoad();
    void load();
    void save();

public:

    explicit KijeDocApp(QObject* parent = nullptr);
    ~KijeDocApp();

    QQmlComponent* viewDelegate() const;
    void setViewDelegate(QQmlComponent* viewDelegate);
    Q_SIGNAL void viewDelegateChanged();

    Q_INVOKABLE void newWindow();

    void classBegin() override;
    void componentComplete() override;

};

class KijeApp : public KijeAbstractApp
{

    Q_OBJECT

public:

    explicit KijeApp(QObject* parent = nullptr);
    ~KijeApp();

};