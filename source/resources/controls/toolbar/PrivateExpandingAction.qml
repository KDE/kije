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

Action {
    identifier: "expanding"
    displayName: "Expanding Spacer"
    displayComponent: Rectangle {
        anchors.fill: parent
        implicitHeight: measuring.height
        color: toolbarRoot.editMode ? Kirigami.ColorUtils.scaleColor(Kirigami.Theme.textColor, {alpha:-90}) : "transparent"
        border {
            color: Kirigami.Theme.textColor
            width: toolbarRoot.editMode ? 2 : 0
        }
        Layout.fillWidth: true
        QtObject {
            property var btn: QQC2.Button {
                id: measuring
                text: "measuring"
            }
        }
    }
}