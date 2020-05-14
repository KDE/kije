#include "dock_private.h"

QQuickItem* DockPrivate::rootItem(QQuickItem *item)
{
    auto parent = item;
    QQuickItem *ret = item;
    while (parent != nullptr) {
        ret = parent;
        parent = parent->parentItem();
    }
    return ret;
}

bool DockPrivate::locked()
{
    return m_semaphore > 0;
}

void DockPrivate::semaphoreUp()
{
    m_semaphore++;
    Q_EMIT lockedChanged();
}

void DockPrivate::semaphoreDown()
{
    m_semaphore--;
    Q_EMIT lockedChanged();
}