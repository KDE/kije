/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include <KSharedConfig>
#include <KConfigGroup>

#include <QQmlEngine>
#include <QQmlProperty>
#include <QUuid>

#include "kije_app_doc_p.h"
#include "kije_page.h"

#include <QtQuick/private/qquickevents_p_p.h>

KijeDocApp::KijeDocApp(QObject* parent) : KijeAbstractApp(parent), d(new Private)
{

}

KijeDocApp::~KijeDocApp()
{
    save();
}

QQmlComponent* KijeDocApp::viewDelegate() const
{
    return d->viewDelegate;
}

void KijeDocApp::setViewDelegate(QQmlComponent* viewDelegate)
{
    if (d->viewDelegate == viewDelegate) {
        return;
    }

    d->viewDelegate = viewDelegate;
    Q_EMIT viewDelegateChanged();
}

inline QString ident(const QUuid& uuid)
{
    return QString("_kije_doc_window_%1").arg(uuid.toString());
}

inline QString newIdent()
{
    return ident(QUuid::createUuid());
}

void KijeDocApp::newWindow(const QString& ident)
{
    auto win = new KijeWindow();

    auto obj = d->viewDelegate->beginCreate(qmlContext(this));
    auto page = qobject_cast<KijePage*>(obj);
    if (!page) {
        auto dat = d->viewDelegate->errorString().toLocal8Bit();
        qFatal("KijeDocApp::firstLoad: the viewDelegate of a KijeDocApp must be a KijePage!\n%s", dat.data());
    }

    connect(win, &KijeWindow::writeState, page, &KijePage::writeState);
    connect(win, &KijeWindow::restoreState, page, &KijePage::restoreState);

    win->setIdentifier(ident);
    qmlEngine(this)->setContextForObject(win, qmlContext(this));
    win->componentComplete();
    page->setParent(win);

    connect(win, &QWindow::activeChanged, this, [this, win, page]() {
        if (win->isActive()) {
            d->activePage = page;
            Q_EMIT activePageChanged();
        }
    });
    connect(win, &QQuickWindow::closing, this, [this, win, page]() {
        if (d->windows.length() < 2) {
            return;
        }

        auto config = KSharedConfig::openConfig();
        auto group = config->group("org.kde.kije").group("views");
        group.deleteGroup(win->identifier());

        d->windows.removeAll(win);
        page->deleteLater();
        win->deleteLater();
    });

    d->viewDelegate->completeCreate();

    page->setParentItem(win->contentItem());
    qvariant_cast<QObject*>(page->property("anchors"))->setProperty("fill", QVariant::fromValue(page->parentItem()));
    d->windows << win;

    win->show();
}

void KijeDocApp::firstLoad()
{
    newWindow(newIdent());
}

KijePage* KijeDocApp::activePage() const
{
    return d->activePage;
}

void KijeDocApp::load()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("views");

    if (group.groupList().isEmpty()) {
        firstLoad();
        return;
    }

    for (const auto& it : group.groupList()) {
        newWindow(it);
    }
}

void KijeDocApp::save()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("views");

    for (auto it : d->windows) {
        group.group(it->identifier()).writeEntry("_dummy", true);
        delete it;
    }
}

void KijeDocApp::newWindow()
{
    newWindow(newIdent());
}

void KijeDocApp::classBegin()
{
}

void KijeDocApp::componentComplete()
{
    load();
}
