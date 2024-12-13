#pragma once

#include <QGraphicsObject>

class CellSideGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    CellSideGraphicsObject(Qt::Orientation orientation, QGraphicsItem *parent = nullptr);

    void setLength(int length);
    void setThickness(int thickness);
    void setColor(const QColor &color);
    void setOrientation(Qt::Orientation orientation);

    QRectF boundingRect() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int m_length = 5;
    int m_thickness = 1;
    Qt::Orientation m_orientation;
    QColor m_color = Qt::black;
};

