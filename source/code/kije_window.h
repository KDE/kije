/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QQuickWindow>

class KijeAction;
class KijeWindow;

class KijeWindow : public QQuickWindow, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    struct Private;
    QScopedPointer<Private> d;

    Q_PROPERTY(QJSValue state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)

    void saveScreen();
    void restoreScreen();

public:

    explicit KijeWindow(QWindow* parent = nullptr);
    ~KijeWindow();

    QJSValue state() const;
    void setState(const QJSValue& state);
    Q_SIGNAL void stateChanged();

    QString identifier() const;
    void setIdentifier(const QString& identifier);
    Q_SIGNAL void identifierChanged();

    void classBegin() override;
    void componentComplete() override;

};
