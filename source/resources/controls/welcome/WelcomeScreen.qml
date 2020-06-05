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

Item {
    default property list<WelcomeSection> sections

    RowLayout {
        children: parent.sections
        anchors.centerIn: parent
        spacing: Kirigami.Units.largeSpacing*2
    }
}