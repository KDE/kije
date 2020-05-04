import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kijetesantakalu 1.0
import org.kde.kijetesantakalu.private 1.0

QQC2.ToolBar {
    id: toolbarRoot

    property list<Kirigami.Action> actions
    QQC2.CheckBox {
        id: editBox
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }
    RowLayout {
        id: toolbarRow
        anchors.fill: parent
        spacing: 0
        Repeater {
            model: actions
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
                        let calc = ToolbarPrivate.calculateDragIndex(toolbarRow, button, dragArea.mapToItem(toolbarRow, dragArea.mouseX, 0).x)
                        let actionArray = Array.from(toolbarRoot.actions)
                        actionArray.splice(index, 0, actionArray.splice(calc, 1)[0]);
                        toolbarRoot.actions = actionArray
                    }
                }
            }
        }
    }
}