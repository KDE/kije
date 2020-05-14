#pragma once

#include <QObject>
#include <QQuickItem>

class DockPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool locked READ locked NOTIFY lockedChanged)
public:
    Q_INVOKABLE QQuickItem* rootItem(QQuickItem *item);
    bool locked();
    Q_SIGNAL void lockedChanged();
    Q_INVOKABLE void semaphoreUp();
    Q_INVOKABLE void semaphoreDown();
private:
    int m_semaphore;
};