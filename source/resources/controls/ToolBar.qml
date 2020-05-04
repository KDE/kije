import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kijetesantakalu 1.0
import org.kde.kijetesantakalu.private 1.0

QQC2.ToolBar {
    id: toolbarRoot

    z: 100
    property list<Kirigami.Action> defaultActions
    property list<Kirigami.Action> potentialActions

    QtObject {
        id: _private
        property list<Kirigami.Action> actions
    }

    Component.onCompleted: {
        _private.actions = toolbarRoot.defaultActions
    }

    QQC2.CheckBox {
        id: editBox
        text: "Edit Mode"
        anchors.right: parent.right
        anchors.top: parent.bottom
        anchors.topMargin: Kirigami.Units.largeSpacing
    }
    Kirigami.ShadowedRectangle {
        id: toolsBox
        anchors {
            left: parent.left
            leftMargin: Kirigami.Units.largeSpacing*10
            right: parent.right
            rightMargin: Kirigami.Units.largeSpacing*10
            top: parent.bottom
            topMargin: Kirigami.Units.largeSpacing * 2
        }
        z: 98
        shadow {
            color: Qt.rgba(0,0,0,0.3)
            size: 32
        }
        border {
            color: Qt.rgba(0,0,0,0.2)
            width: 2
        }
        corners {
            topLeftRadius: 20
            topRightRadius: 20
            bottomLeftRadius: 20
            bottomRightRadius: 20
        }
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
                PropertyChanges { target: toolsBox; opacity: 1 }
            },
            State {
                name: 'invisible'
                when: !editBox.checked
                PropertyChanges { target: toolsBox; opacity: 0 }
            }
        ]
        GridLayout {
            id: picturesColumn
            anchors.fill: parent
            anchors.margins: Kirigami.Units.largeSpacing

            rowSpacing: Kirigami.Units.smallSpacing
            columnSpacing: Kirigami.Units.smallSpacing
            columns: Math.floor((width) / (Kirigami.Units.gridUnit * 2))

            Repeater {
                model: toolbarRoot.potentialActions
                delegate: QQC2.ToolButton {
                    id: button
                    text: modelData.text
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    onClicked: {
                        let actions = Array.from(_private.actions)
                        actions.push(modelData)
                        _private.actions = actions
                    }
                }
            }
        }
    }
    RowLayout {
        id: toolbarRow
        anchors.fill: parent
        spacing: 0
        z: 99
        Repeater {
            model: _private.actions
            delegate: QQC2.ToolButton {
                id: button
                text: modelData.text
                onClicked: modelData.trigger()
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Drag.active: dragArea.drag.active

                MouseArea {
                    id: dragArea
                    anchors.fill: parent
                    enabled: editBox.checked

                    drag.target: parent
                    drag.threshold: 2
                    onReleased: {
                        let mapped = dragArea.mapToItem(toolbarRow, dragArea.mouseX, dragArea.mouseY)
                        if (mapped.y > toolbarRow.height) {
                            let actionArray = Array.from(_private.actions)
                            actionArray.splice(index, 1);
                            _private.actions = actionArray
                        }
                        let calc = ToolbarPrivate.calculateDragIndex(toolbarRow, button, mapped.x)
                        let actionArray = Array.from(_private.actions)
                        actionArray.splice(index, 0, actionArray.splice(calc, 1)[0]);
                        _private.actions = actionArray
                    }
                }
            }
        }
    }
}