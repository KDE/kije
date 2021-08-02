/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QObject>
#include <QQmlListProperty>

class QPlatformMenu;
class QPlatformMenuBar;
class QPlatformMenuItem;

class KijeAction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QVariant shortcut READ shortcut WRITE setShortcut NOTIFY shortcutChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

    Q_PROPERTY(QQmlListProperty<KijeAction> childActions READ childActions)
    Q_CLASSINFO("DefaultProperty", "childActions")

    struct Private;
    QScopedPointer<Private> d;

public:

    explicit KijeAction(QObject* parent = nullptr);
    ~KijeAction();

    QQmlListProperty<KijeAction> childActions();
    const QList<KijeAction*> cxxChildActions();

    // implemented in kije_app_abstract.cpp
    // due to using same private API + closeness
    // in usage
    void intoPlatformMenu(QPlatformMenu* of);
    QPlatformMenuItem* intoPlatformMenuItem(QPlatformMenu* of);

    QString identifier() const;
    void setIdentifier(const QString& identifier);
    Q_SIGNAL void identifierChanged();

    QString text() const;
    void setText(const QString& text);
    Q_SIGNAL void textChanged();

    QVariant shortcut() const;
    void setShortcut(const QVariant& shortcut);
    Q_SIGNAL void shortcutChanged();

    bool enabled() const;
    void setEnabled(bool enabled);
    Q_SIGNAL void enabledChanged();

    Q_SIGNAL void triggered();
};