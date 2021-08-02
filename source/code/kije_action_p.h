/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include <QKeySequence>
#include <optional>

#include "kije_action.h"

struct KijeAction::Private
{
    QString identifier;
    QString text;

    QVariant shortcut;
    std::optional<int> shortcutHandle;

    bool enabled = true;

    QList<KijeAction*> actions;
};

inline auto toSequence(const QVariant& shortcut) -> QKeySequence
{
    if (!shortcut.isValid() || shortcut.isNull()) return QKeySequence();

    QKeySequence seq;

    // i don't think there's anything other than a string or a standardkey deal
    if (shortcut.type() == QVariant::Int) {
        seq = static_cast<QKeySequence::StandardKey>(shortcut.toInt());
    } else if (shortcut.type() == QVariant::String) {
        seq = QKeySequence::fromString(shortcut.toString());
    } else {
        qFatal("shortcut has to be a StandardKey or a string representing a shortcut %d", shortcut.type());
    }

    return seq;
}
