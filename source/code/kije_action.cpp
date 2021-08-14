/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include <QKeySequence>
#include <QQuickItem>
#include <QQuickRenderControl> 
#include <QQuickWindow>

#include <KAuthorized>

#include <QtGui/private/qguiapplication_p.h>

#include "kije_action_p.h"

KijeAction::KijeAction(QObject* parent) : QObject(parent), d(new Private)
{

}

KijeAction::~KijeAction()
{

}

#define synthesize_set(name, signal) \
if (d->name == name) {\
    return;\
}\
d->name = name; \
Q_EMIT signal();

QString KijeAction::identifier() const
{
    return d->identifier;
}

void KijeAction::setIdentifier(const QString& identifier)
{
    synthesize_set(identifier, identifierChanged)
}

QString KijeAction::text() const
{
    return d->text;
}

void KijeAction::setText(const QString& text)
{
    synthesize_set(text, textChanged);
}

QString KijeAction::editLabel() const
{
    return d->editLabel.isEmpty() ? d->text : d->editLabel;
}

void KijeAction::setEditLabel(const QString& editLabel)
{
    synthesize_set(editLabel, editLabelChanged);
}

QQmlListProperty<KijeAction> KijeAction::childActions()
{
    return QQmlListProperty<KijeAction>{this, &d->actions};
}

const QList<KijeAction*> KijeAction::cxxChildActions()
{
    return d->actions;
}

QVariant KijeAction::shortcut() const
{
    return d->shortcut;
}

// determines whether or not an item is ready to
// accept shortcuts, needed for the shortcutmap
// implementation
bool matcher(QObject *forObject, Qt::ShortcutContext context)
{
    if (context == Qt::ApplicationShortcut) {
        return true;
    }

    // we aren't widgets, so WidgetShortcut
    // and WidgetWithChildrenShortcut aren't
    // applicable here
    if (context != Qt::WindowShortcut) {
        return false;
    }

    QQuickItem* climbingIten = nullptr;
    QObject* climbingObject = forObject;

    // yay for tree climbing
    while (climbingObject && !climbingObject->isWindowType()) {
        climbingIten = qobject_cast<QQuickItem *>(climbingObject);
        if (climbingIten && climbingIten->window()) {
            climbingObject = climbingIten->window();
            break;
        }
        climbingObject = climbingObject->parent();
    }

    // for reasons, the qquickwindow is not necessarily the actual qwindow
    // that interacts with the windowing system
    auto actualWindow = QQuickRenderControl::renderWindowFor(qobject_cast<QQuickWindow *>(climbingObject));
    if (actualWindow != nullptr) {
        climbingObject = actualWindow;
    }

    return climbingObject && climbingObject == QGuiApplication::focusWindow();
}

void KijeAction::setShortcut(const QVariant& shortcut)
{
    if (d->shortcut == shortcut) {
        return;
    }

    if (d->shortcutHandle.has_value()) {
        // TODO: figure out, do we need the sequence? the handle + object
        // seems like it should be enough, but the removeShortcut argument
        // takes a sequence
        auto seq = toSequence(d->shortcut);

        QGuiApplicationPrivate::instance()->shortcutMap.removeShortcut(*d->shortcutHandle, this, seq);
    }

    d->shortcut = shortcut;

    auto seq = toSequence(shortcut);
    if (!seq.isEmpty()) {
        d->shortcutHandle =
            QGuiApplicationPrivate::instance()->shortcutMap.addShortcut(this, seq, Qt::WindowShortcut, matcher);
    } else {
        d->shortcutHandle.reset();
    }

    Q_EMIT shortcutChanged();
}

bool KijeAction::enabled() const
{
    if (!KAuthorized::authorizeAction(d->identifier)) {
        return false;
    }
    return d->enabled;
}

void KijeAction::setEnabled(bool enabled)
{
    synthesize_set(enabled, enabledChanged)
}

