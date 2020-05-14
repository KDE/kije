import QtQuick 2.12
import org.kde.kirigami 2.12 as Kirigami
import QtQuick.Controls 2.13 as QQC2
import QtQuick.Layouts 1.12
import org.kde.kijetesantakalu 1.0

Kirigami.AbstractApplicationWindow {
    property alias toolbar: __toolbar
    default property alias children: __nestedColumn.children
    property alias layers: __layers
    property alias stack: __stack

    PrivateStackView {
        id: __layers
        anchors.fill: parent
        initialItem: ColumnLayout {
            anchors.fill: parent
            spacing: 0

            ToolBar {
                id: __toolbar

                identifier: "kijetesantakalu-applicationwindow-primary"

                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            }
            PrivateStackView {
                id: __stack
                initialItem: ColumnLayout {
                    id: __nestedColumn

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}