/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.15
import org.kde.kije 1.0

Action {
    id: editAction

    property Item field: (rootWindow.activeFocusItem instanceof TextEdit || rootWindow.activeFocusItem instanceof TextInput) ? rootWindow.activeFocusItem : null

    text: "Edit" // todo: i18n

    Action {
        enabled: editAction.field !== null && editAction.field.selectedText
        text: "Cut" // todo: i18n
        shortcut: StandardKey.Cut
        onTriggered: editAction.field.cut()
    }
    Action {
        enabled: editAction.field !== null && editAction.field.selectedText
        text: "Copy" // todo: i18n
        shortcut: StandardKey.Copy
        onTriggered: editAction.field.copy()
    }
    Action {
        enabled: editAction.field !== null && editAction.field.canPaste
        text: "Paste" // todo: i18n
        shortcut: StandardKey.Paste
        onTriggered: editAction.field.paste()
    }

    Action {
        enabled: editAction.field !== null && editAction.field.selectedText !== ""
        text: "Delete" // todo: i18n
        onTriggered: editAction.field.remove(editAction.field.selectionStart, editAction.field.selectionEnd)
    }

    Action {
        enabled: editAction.field !== null
        text: "Select All" // todo: i18n
        shortcut: StandardKey.SelectAll
        onTriggered: editAction.field.selectAll()
    }
}
