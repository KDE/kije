/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.12
import org.kde.kirigami 2.12 as Kirigami

Kirigami.Action {
    property string displayName
    property string identifier
    property string defaultShortcut
    shortcut: defaultShortcut

    property bool persistCheckable
}