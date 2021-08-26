#include "kije_widget_embed_p.h"

#ifdef USE_KIJE_WIDGET_EMBED

#include <QApplication>
#include <QHoverEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QQuickWindow>
#include <QWidget>

#include <QTextEdit>
#include <QPushButton>

KijeWidgetEmbed::KijeWidgetEmbed(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , d(new Private)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);

    auto btn = new QTextEdit("which one doesn't belong?");
    setWidget(btn);
}

KijeWidgetEmbed::~KijeWidgetEmbed() = default;

void KijeWidgetEmbed::componentComplete()
{
    QQuickPaintedItem::componentComplete();
}

bool KijeWidgetEmbed::eventFilter(QObject *watched, QEvent *event)
{
    if (watched != d->widget.data()) {
        return QQuickPaintedItem::eventFilter(watched, event);
    }

    switch (event->type()) {
    case QEvent::Show:
    case QEvent::UpdateRequest:
        update();
        doGeometry();
        break;
    default:
        break;
    }

    return QQuickPaintedItem::eventFilter(watched, event);
}

QWidget* KijeWidgetEmbed::widget() const
{
    return d->widget;
}

void KijeWidgetEmbed::setWidget(QWidget* widget)
{
    if (d->widget == widget) {
        return;
    }

    if (d->widget) {
        d->widget->removeEventFilter(this);
    }


    d->widget = widget;
    if (d->widget) {
        d->widget->setAttribute(Qt::WA_DontShowOnScreen);

        d->widget->ensurePolished();
        d->widget->installEventFilter(this);
        d->widget->show();
    }

    doGeometry();
    Q_EMIT widgetChanged();
}

void KijeWidgetEmbed::paint(QPainter *painter)
{
    if (!d->widget || !d->widget->isVisible()) {
        return;
    }

    d->widget->render(painter);
}

// implements the functionality of QApplicationPrivate::dispatchEnterLeave
void KijeWidgetEmbed::dispatchEnterLeave(QWidget* enter, QWidget* leave, const QPointF &globalPosF)
{
    if (!enter && !leave)
        return;

    if (enter == leave)
        return;

    QWidgetList leaveList;
    QWidgetList enterList;

    bool sameWindow = leave && enter && leave->window() == enter->window();
    const auto allParents = [](QWidget* of, QWidgetList& out) {
        auto *w = of;

        do {
            out.append(w);
        } while (!w->isWindow() && (w = w->parentWidget()));
    };

    if (leave && !sameWindow) {
        allParents(leave, leaveList);
    }
    if (enter && !sameWindow) {
        allParents(enter, leaveList);
    }

    if (sameWindow) {
        int enterDepth = 0;
        int leaveDepth = 0;
        auto *e = enter;
        while (!e->isWindow() && (e = e->parentWidget()))
            enterDepth++;
        auto *l = leave;
        while (!l->isWindow() && (l = l->parentWidget()))
            leaveDepth++;
        QWidget* wenter = enter;
        QWidget* wleave = leave;
        while (enterDepth > leaveDepth) {
            wenter = wenter->parentWidget();
            enterDepth--;
        }
        while (leaveDepth > enterDepth) {
            wleave = wleave->parentWidget();
            leaveDepth--;
        }
        while (!wenter->isWindow() && wenter != wleave) {
            wenter = wenter->parentWidget();
            wleave = wleave->parentWidget();
        }
        for (auto *w = leave; w != wleave; w = w->parentWidget())
            leaveList.append(w);
        for (auto *w = enter; w != wenter; w = w->parentWidget())
            enterList.append(w);
    }

    const auto globalPos = globalPosF.toPoint();

    QEvent leaveEvent(QEvent::Leave);
    for (auto* w : leaveList) {
        if (!QApplication::activeModalWidget()) {
            QApplication::sendEvent(w, &leaveEvent);
            if (w->testAttribute(Qt::WA_Hover)) {
                QHoverEvent he(QEvent::HoverLeave, QPoint(-1, -1), w->mapFromGlobal(globalPos), QApplication::keyboardModifiers());
                QApplication::sendEvent(w, &he);
            }
        }
    }

    if (!enterList.isEmpty()) {
        const QPoint windowPos = qAsConst(enterList).back()->window()->mapFromGlobal(globalPos);

        for (auto it = enterList.crbegin(), end = enterList.crend(); it != end; ++it) {
            auto *w = *it;

            const QPointF localPos = w->mapFromGlobal(globalPos);
            QEnterEvent enterEvent(localPos, windowPos, globalPosF);
            QApplication::sendEvent(w, &enterEvent);

            if (w->testAttribute(Qt::WA_Hover)) {
                QHoverEvent he(QEvent::HoverEnter, localPos, QPoint(-1, -1), QApplication::keyboardModifiers());
                QApplication::sendEvent(w, &he);
            }
        }
    }
}

void KijeWidgetEmbed::hoverEnterEvent(QHoverEvent *event)
{
    const auto wid = d->widget;

    if (!wid || !wid->isVisible()) {
        return;
    }

    QPointF localPos = event->pos();

    QWidget *child = wid->childAt(localPos.toPoint());
    QWidget *receiver = child ? child : wid.data();

    dispatchEnterLeave(receiver, d->lastHovered, mapToGlobal(event->pos()));

    d->lastHovered = receiver;

    localPos = receiver->mapFrom(d->widget.data(), localPos.toPoint());

    QMouseEvent mouseEvent(
        QEvent::Enter,
        localPos,
        receiver->mapTo(receiver->topLevelWidget(), localPos.toPoint()),
        receiver->mapToGlobal(localPos.toPoint()),
        Qt::NoButton,
        {} /*buttons*/,
        event->modifiers()
    );

    qApp->sendEvent(receiver, &mouseEvent);

    event->setAccepted(mouseEvent.isAccepted());
}

void KijeWidgetEmbed::hoverMoveEvent(QHoverEvent *event)
{
    const auto wid = d->widget;

    if (!wid || !wid->isVisible()) {
        return;
    }

    QPointF localPos = event->pos();

    QWidget *child = wid->childAt(localPos.toPoint());
    QWidget *receiver = child ? child : wid.data();

    dispatchEnterLeave(receiver, d->lastHovered, mapToGlobal(event->pos()));

    d->lastHovered = receiver;

    localPos = receiver->mapFrom(d->widget.data(), localPos.toPoint());

    QMouseEvent mouseEvent(
        QEvent::MouseMove,
        localPos,
        receiver->mapTo(receiver->topLevelWidget(), localPos.toPoint()),
        receiver->mapToGlobal(localPos.toPoint()),
        Qt::NoButton,
        {} /*buttons*/,
        event->modifiers()
    );

    qApp->sendEvent(receiver, &mouseEvent);

    event->setAccepted(mouseEvent.isAccepted());
}

void KijeWidgetEmbed::dispatchMouseEvent(QMouseEvent *event)
{
    const auto wid = d->widget;

    QPointF localPos = event->pos();

    QWidget *child = wid->childAt(localPos.toPoint());
    QWidget *receiver = child ? child : wid.data();

    localPos = receiver->mapFrom(d->widget.data(), localPos.toPoint());

    QMouseEvent translated(
        event->type(),
        localPos,
        event->button(),
        event->buttons(),
        event->modifiers()
    );

    qApp->sendEvent(receiver, &translated);

    event->setAccepted(translated.isAccepted());
}

void KijeWidgetEmbed::mouseMoveEvent(QMouseEvent *event)
{
    dispatchMouseEvent(event);
}

void KijeWidgetEmbed::mousePressEvent(QMouseEvent *event)
{
    dispatchMouseEvent(event);
}

void KijeWidgetEmbed::mouseReleaseEvent(QMouseEvent *event)
{
    dispatchMouseEvent(event);
}

void KijeWidgetEmbed::hoverLeaveEvent(QHoverEvent *event)
{
    if (!d->lastHovered) {
        return;
    }

    dispatchEnterLeave(nullptr, d->lastHovered, mapToGlobal(event->pos()));
    d->lastHovered = nullptr;
}

void KijeWidgetEmbed::doGeometry()
{
    if (!d->widget) {
        return;
    }

    const auto sh = d->widget->sizeHint();

    setImplicitSize(sh.width(), sh.height());
}

void KijeWidgetEmbed::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (d->widget && newGeometry != oldGeometry) {
        d->widget->resize(qRound(newGeometry.width()), qRound(newGeometry.height()));
    }

    doGeometry();

    QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);
}

#endif
