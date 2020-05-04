#pragma once

#include <QObject>
#include <QQuickItem>

class ToolbarPrivate : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE int calculateDragIndex(QQuickItem *rowLayout, QQuickItem *draggee, qreal currentDragX);
};