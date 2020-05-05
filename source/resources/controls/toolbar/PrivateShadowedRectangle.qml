import QtQuick 2.12
import org.kde.kirigami 2.12 as Kirigami

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
}