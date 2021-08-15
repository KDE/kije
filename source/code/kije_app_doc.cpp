/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include <KSharedConfig>
#include <KConfigGroup>

#include <QQmlProperty>
#include <QUuid>

#include "kije_app_doc_p.h"
#include "kije_page.h"

KijeDocApp::KijeDocApp(QObject* parent) : KijeAbstractApp(parent), d(new Private)
{

}

KijeDocApp::~KijeDocApp()
{

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

void KijeDocApp::firstLoad()
{
    auto win = new KijeWindow();
    win->setIdentifier(newIdent());

    auto obj = d->viewDelegate->beginCreate(qmlContext(this));
    auto page = qobject_cast<KijePage*>(obj);
    if (!page) {
        auto dat = d->viewDelegate->errorString().toLocal8Bit();
        qFatal("KijeDocApp::firstLoad: the viewDelegate of a KijeDocApp must be a KijePage!\n%s", dat.data());
    }

    page->setParentItem(win->contentItem());
    qvariant_cast<QObject*>(page->property("anchors"))->setProperty("fill", QVariant::fromValue(page->parentItem()));
    d->viewDelegate->completeCreate();

    win->componentComplete();
    win->show();
}

void KijeDocApp::load()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije").group("views");

    if (group.keyList().isEmpty()) {
        firstLoad();
        return;
    }
}

void KijeDocApp::save()
{

}

void KijeDocApp::classBegin()
{
}

void KijeDocApp::componentComplete()
{
    load();
}
