/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include <QJsonDocument>
#include <QJSValue>
#include <QQmlEngine>
#include <QScreen>

#include <KConfigGroup>
#include <KSharedConfig>

#include "kije_window.h"

struct KijeWindow::Private
{
    QJSValue state;
    QString identifier;
};

KijeWindow::KijeWindow(QWindow* parent) : QQuickWindow(parent), d(new Private)
{

}

KijeWindow::~KijeWindow()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("windows").group(d->identifier);

    auto doku = QJsonDocument::fromVariant(d->state.toVariant());
    group.writeEntry("state", doku.toJson());
    group.config()->sync();

    saveScreen();
}

QJSValue KijeWindow::state() const
{
    return d->state;
}

void KijeWindow::setState(const QJSValue& state)
{
    d->state = state;
    Q_EMIT stateChanged();
}

QString KijeWindow::identifier() const
{
    return d->identifier;
}

void KijeWindow::setIdentifier(const QString& identifier)
{
    if (d->identifier == identifier) {
        return;
    }

    d->identifier = identifier;
    Q_EMIT identifierChanged();
}


void KijeWindow::classBegin()
{

}

void KijeWindow::saveScreen()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("windows").group(d->identifier);

    group.writeEntry("geometry", geometry());
}

void KijeWindow::restoreScreen()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("windows").group(d->identifier);

    if (!group.hasKey("geometry")) {
        return;
    }

    setGeometry(group.readEntry("geometry", QRect()));
}

void KijeWindow::componentComplete()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("windows").group(d->identifier);

    restoreScreen();

    if (!group.hasKey("state")) {
        return;
    }

    auto doku = QJsonDocument::fromJson(group.readEntry("state", QByteArray()));

    d->state = qmlEngine(this)->evaluate(doku.toJson());
    Q_EMIT stateChanged();
}
