#pragma once

#ifdef USE_KIJE_WIDGET_EMBED

#include <QPointer>
#include <QQuickPaintedItem>

class QWidget;

class KijeWidgetEmbed : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QWidget* widget READ widget WRITE setWidget NOTIFY widgetChanged)

    struct Private;
    QScopedPointer<Private> d;

public:
    explicit KijeWidgetEmbed(QQuickItem *parent = nullptr);
    ~KijeWidgetEmbed() override;

    QWidget* widget() const;
    void setWidget(QWidget* widget);
    Q_SIGNAL void widgetChanged();

    void componentComplete() override;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

    void paint(QPainter *painter) override;
    void doGeometry();

    void hoverEnterEvent(QHoverEvent *event) override;
    void hoverMoveEvent(QHoverEvent *event) override;
    void hoverLeaveEvent(QHoverEvent *event) override;

    void dispatchMouseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void dispatchEnterLeave(QWidget* enter, QWidget* leave, const QPointF &globalPosF);

};

#endif
