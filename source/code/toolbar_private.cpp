#include "toolbar_private.h"

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