import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kije 1.0
import org.kde.kije.private 1.0

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
    Component {
        id: buttonComponent
        QQC2.ToolButton {
            text: delegateRoot.action.text
            onClicked: delegateRoot.action.trigger()
        }
    }
}