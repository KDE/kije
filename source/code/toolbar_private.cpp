/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "toolbar_private.h"
#include <KSharedConfig>
#include <KConfigGroup>

int ToolbarPrivate::calculateDragIndex(QQuickItem *rowLayout, QQuickItem *draggee, qreal currentDragX)
{
    QList<int> midpoints;
    for (const auto &item: rowLayout->childItems()) {
        if (item != draggee) {
            midpoints << (item->x() + (item->width() / 2));
        }
    }
    for (int leftIndex = 0, rightIndex = 1; rightIndex < midpoints.length();) {
        if (midpoints[leftIndex] < currentDragX && currentDragX <= midpoints[rightIndex]) {
            return rightIndex;
        }
        leftIndex++;
        rightIndex++;
    }
    return [midpoints,currentDragX]() {
        if (currentDragX < midpoints.first()) {
            // we're to the left of the list
            return 0;
        } else {
            // we're to the right of the list
            return midpoints.length()-1;
        }
    }();
};

QVariantList ToolbarPrivate::recallToolbar(const QString &id)
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije");
    auto toolbarsGroup = group.group("toolbars");
    return toolbarsGroup.readEntry(id, QVariantList());
}

void ToolbarPrivate::serializeToolbar(const QString &id, QQmlListReference data)
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije");
    auto toolbarsGroup = group.group("toolbars");
    QVariantList list;
    for (int index = 0; index < data.count(); index++) {
        list << data.at(index)->property("identifier");
    }
    toolbarsGroup.writeEntry(id, list);
    toolbarsGroup.config()->sync();
}

void ToolbarPrivate::forgetToolbar(const QString &id)
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("org.kde.kije");
    auto toolbarsGroup = group.group("toolbars");
    toolbarsGroup.writeEntry(id, "");
    toolbarsGroup.config()->sync();
}