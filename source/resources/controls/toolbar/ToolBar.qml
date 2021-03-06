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

QQC2.ToolBar {
    id: toolbarRoot

    property alias editMode: editBox.checked

    z: 100
    property string identifier: ""
    property var defaultActions: []
    property list<Action> potentialActions

    QQC2.CheckBox {
        id: editBox
        text: "Edit Mode"
        anchors.right: parent.right
        anchors.top: parent.bottom
        anchors.topMargin: Kirigami.Units.largeSpacing
    }

    QtObject {
        id: _private
        property list<Action> actions
        property list<Action> allActions
        property list<Action> alwaysPresentActions: [
            PrivateExpandingAction{}
        ]
        function pushActions(list) {
            for (let action of list) {
                for (let i = 0; i < _private.allActions.length; i++) {
                    let comp = _private.allActions[i]
                    if (action.identifier == comp.identifier) {
                        _private.actions.push(comp)
                        ToolbarPrivate.setOn(action, comp)
                    }
                }
            }
        }
        function save() {
            if (toolbarRoot.identifier != "") {
                ToolbarPrivate.serializeToolbar(toolbarRoot.identifier, _private.actions)
            }
        }
        Component.onDestruction: save()
    }

    function syncActions() {
        let pA = Array.from(toolbarRoot.potentialActions)
        let aPA = Array.from(_private.alwaysPresentActions)
        _private.allActions = pA.concat(aPA)
    }

    onDefaultActionsChanged: syncActions()
    onPotentialActionsChanged: syncActions()

    Component.onCompleted: {
        _private.pushActions(toolbarRoot.defaultActions)
        if (toolbarRoot.identifier != "") {
            let list = ToolbarPrivate.recallToolbar(toolbarRoot.identifier)
            if (list != []) {
                _private.actions = []
                _private.pushActions(list)
            }
        }
        syncActions()
    }

    PrivateShadowedRectangle {
        id: toolsBox
        z: 98
        height: 300
        transitions: [
            Transition {
                NumberAnimation {
                    properties: "opacity"
                    easing.type: Easing.InOutQuad
                }
            }
        ]
        states: [
            State {
                name: 'visible'
                when: editBox.checked
                PropertyChanges { target: toolsBox; opacity: 1; visible: true }
            },
            State {
                name: 'invisible'
                when: !editBox.checked
                PropertyChanges { target: toolsBox; opacity: 0; visible: false }
            }
        ]
        DropArea {
            anchors.fill: parent
            enabled: toolbarRoot.editMode
            onDropped: function(event) {
                if (event.source.parent == toolbarRow) {
                    let actionArray = Array.from(_private.actions)
                    actionArray.splice(event.source.exposedIndex, 1)
                    _private.actions = actionArray
                    _private.save()
                }
            }
        }
        GridLayout {
            id: picturesColumn
            anchors.fill: parent
            anchors.margins: Kirigami.Units.largeSpacing

            rowSpacing: Kirigami.Units.largeSpacing
            columnSpacing: Kirigami.Units.largeSpacing
            columns: Math.floor((width) / (Kirigami.Units.gridUnit * 9))

            Repeater {
                model: _private.allActions
                delegate: ColumnLayout {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    PrivateActionDelegate {
                        action: modelData
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Drag.active: dragArea.drag.active
                        Drag.dragType: Drag.Automatic
                        MouseArea {
                            id: dragArea
                            anchors.fill: parent
                            drag.target: parent
                            onClicked: {
                                let actions = Array.from(_private.actions)
                                actions.push(modelData)
                                _private.actions = actions
                                _private.save()
                            }
                        }
                    }
                    QQC2.Label {
                        text: modelData.displayName
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }
        }
        QQC2.Button {
            anchors {
                bottom: parent.bottom
                right: parent.right
                margins: Kirigami.Units.largeSpacing
            }
            text: "Reset"
            onClicked: {
                _private.actions = toolbarRoot.defaultActions
                _private.save()
            }
        }
    }

    implicitHeight: toolbarRow.implicitHeight + topPadding + bottomPadding
    implicitWidth: toolbarRow.implicitWidth + leftPadding + rightPadding

    RowLayout {
        id: toolbarRow
        spacing: 4
        anchors {
            left: parent.left
            right: parent.right
        }
        z: 99
        Repeater {
            id: repeat
            model: _private.actions
            delegate: PrivateActionDelegate {
                id: actionDelegate
                action: modelData

                property int exposedIndex
                Component.onCompleted: exposedIndex = model.index
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Drag.active: dragArea.drag.active
                Drag.dragType: Drag.Automatic

                MouseArea {
                    id: dragArea
                    anchors.fill: parent
                    enabled: editBox.checked

                    drag.target: parent
                }
            }
        }
    }
    DropArea {
        anchors.fill: toolbarRow
        enabled: toolbarRoot.editMode
        onDropped: function(event) {
            let calc = ToolbarPrivate.calculateDragIndex(toolbarRow, event.source, event.x)
            let actionArray = Array.from(_private.actions)
            if (event.source.parent == toolbarRow) {
                actionArray.splice(event.source.exposedIndex, 0, actionArray.splice(calc, 1)[0])
                _private.actions = actionArray
            } else {
                actionArray.splice(calc, 0, event.source.action)
                _private.actions = actionArray
            }
            _private.save()
        }
    }
}