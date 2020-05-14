import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kijetesantakalu 1.0
import org.kde.kijetesantakalu.private 1.0

Item {
    default property list<WelcomeSection> sections

    RowLayout {
        children: parent.sections
        anchors.centerIn: parent
        spacing: Kirigami.Units.largeSpacing*2
    }
}