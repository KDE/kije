/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.12
import QtQuick.Layouts 1.10
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kije.private 1.0

Item {
    id: __boxRoot

    implicitWidth: __gridLayout.implicitWidth
    implicitHeight: __gridLayout.implicitHeight

    property real spacing: 0
    property int layoutDirection: DockBox.LayoutDirection.Row
    default property list<DockItem> dockItems
    onDockItemsChanged: Array.from(dockItems).forEach(item => item.parent =__gridLayout)

    enum LayoutDirection {
        Row,
        Column
    }

    GridLayout {
        id: __gridLayout
        columnSpacing: spacing
        rowSpacing: spacing
        rows: parent.layoutDirection == DockBox.LayoutDirection.Row ? 1 : dockItems.length
        columns: parent.layoutDirection == DockBox.LayoutDirection.Column ? 1 : dockItems.length
    }
}