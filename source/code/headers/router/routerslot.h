#pragma once

#include <QQuickItem>

class RouterSlot : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)

public:
    QString name;
    Q_SIGNAL void nameChanged();
};
