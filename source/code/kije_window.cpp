/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include <QJsonDocument>
#include <QJSValue>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>
#include <QScreen>

#include <KConfigGroup>
#include <KSharedConfig>
#include <KWindowConfig>

#include "kije_window.h"
#include "kije_app.h"

struct KijeWindow::Private
{
    QQmlEngine* eng = nullptr;
    QString identifier;
};

KijeWindow::KijeWindow(QWindow* parent) : QQuickWindow(parent), d(new Private)
{
}

void KijeWindow::saveState()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("windows").group(d->identifier);

    QJSValue it = d->eng->newObject();
    Q_EMIT writeState(it);

    auto doku = QJsonDocument::fromVariant(it.toVariant());
    group.writeEntry("state", doku.toJson());
    group.config()->sync();

    saveScreen();
}

bool KijeWindow::event(QEvent *event)
{
    if (event->type() == QEvent::Close) {
        saveState();
    }

    return QQuickWindow::event(event);
}

KijeWindow::~KijeWindow()
{
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

    KWindowConfig::saveWindowSize(this, group);
    KWindowConfig::saveWindowPosition(this, group);
}

void KijeWindow::restoreScreen()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("windows").group(d->identifier);

    KWindowConfig::restoreWindowSize(this, group);
    KWindowConfig::restoreWindowPosition(this, group);
}

void KijeWindow::componentComplete()
{
    KijeAbstractApp::instance()->attachMenubar(this);

    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("windows").group(d->identifier);

    restoreScreen();

    if (!group.hasKey("state")) {
        return;
    }

    auto doku = QJsonDocument::fromJson(group.readEntry("state", QByteArray()));

    auto prog = QString("(() => { return %1 })()").arg(doku.toJson().data());
    d->eng = qmlEngine(this);
    Q_EMIT restoreState(qmlEngine(this)->evaluate(prog));
}
