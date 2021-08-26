import QtQuick 2.10
import QtQuick.Layouts 1.10
import QtQuick.Controls 2.12 as QQC2
import org.kde.kije 1.0

QQC2.ApplicationWindow {
    visible: true

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        QQC2.Button {
            text: "which one doesn't belong?"
        }
        WidgetEmbed {
        }
        QQC2.Button {
            text: "which one doesn't belong?"
        }
        Item {
            Layout.fillWidth: true
        }
    }
}
