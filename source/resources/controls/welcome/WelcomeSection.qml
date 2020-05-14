import QtQuick 2.12
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.12 as Kirigami

ColumnLayout {
    property string heading

    Layout.alignment: Qt.AlignTop | Qt.AlignLeft

    Kirigami.Heading {
        text: parent.heading
        level: 2
    }
}