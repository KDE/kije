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

    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)

    void saveScreen();
    void restoreScreen();
    void saveState();

protected:
    bool event(QEvent *event) override;

public:

    explicit KijeWindow(QWindow* parent = nullptr);
    ~KijeWindow();

    Q_SIGNAL void writeState(QJSValue state);
    Q_SIGNAL void restoreState(QJSValue state);

    QString identifier() const;
    void setIdentifier(const QString& identifier);
    Q_SIGNAL void identifierChanged();

    void classBegin() override;
    void componentComplete() override;

};
