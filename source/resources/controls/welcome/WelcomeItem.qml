/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kije 1.0
import org.kde.kije.private 1.0

QQC2.ToolButton {
    property alias iconSource: __icon.source
    property alias heading: __heading.text
    property alias subheading: __subheading.text

    implicitWidth: __row.implicitWidth + (Kirigami.Units.gridUnit*1)
    implicitHeight: __row.implicitHeight + (Kirigami.Units.gridUnit*1)

    RowLayout {
        id: __row
        anchors.centerIn: parent
        Kirigami.Icon {
            id: __icon
            width: Kirigami.Units.iconSizes.medium
            height: Kirigami.Units.iconSizes.medium
        }
        ColumnLayout {
            Kirigami.Heading {
                id: __heading
                level: 3
            }
            Kirigami.Heading {
                id: __subheading
                visible: text != ""
                opacity: 0.8
                level: 5
            }
        }
    }
}