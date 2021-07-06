/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.15
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kije 1.0
import org.kde.kije.private 1.0
import QtQuick.Dialogs 1.3 as Dialogs
import org.kde.kquickcontrols 2.0

Item {
    id: delegateRoot

    width: loady.item.width
    height: loady.item.height
    implicitWidth: loady.item.implicitWidth
    implicitHeight: loady.item.implicitHeight
    Layout.fillWidth: loady.item.Layout.fillWidth
    Layout.fillHeight: loady.item.Layout.fillHeight

    property Kirigami.Action action

    Loader {
        id: loady
        anchors.fill: parent
        sourceComponent: action.displayComponent || buttonComponent
    }
    TapHandler {
        acceptedButtons: Qt.RightButton
        onTapped: diag.open()
    }
    Dialogs.Dialog {
        id: diag

        height: ci.implicitHeight + Kirigami.Units.largeSpacing
        width: ci.implicitWidth + Kirigami.Units.largeSpacing

        component Control : QQC2.Control {}

        contentItem: Control {
            id: ci

            background: Rectangle {
                color: Kirigami.Theme.backgroundColor
            }
            contentItem: RowLayout {
                KeySequenceItem {
                    keySequence: delegateRoot.action.shortcut
                    onCaptureFinished: delegateRoot.action.shortcut = keySequence
                }
            }
        }
    }
    Component {
        id: buttonComponent
        QQC2.Button {
            text: delegateRoot.action.text
            enabled: delegateRoot.action.enabled
            onClicked: delegateRoot.action.trigger()
        }
    }
}