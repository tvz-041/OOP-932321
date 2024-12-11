#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "CellSideGraphicsObject.h"

CellSideGraphicsObject::CellSideGraphicsObject(Qt::Orientation orientation, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , m_orientation(orientation)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
}

void CellSideGraphicsObject::setLength(int length)
{
    m_length = length;
    update();
}

void CellSideGraphicsObject::setThickness(int thickness)
{
    m_thickness = thickness;
    update();
}

void CellSideGraphicsObject::setColor(const QColor &color)
{
    m_color = color;
    update();
}

void CellSideGraphicsObject::setOrientation(Qt::Orientation orientation)
{
    m_orientation = orientation;
    update();
}

QRectF CellSideGraphicsObject::boundingRect() const
{
    if (m_orientation == Qt::Horizontal)
    {
        return QRectF(0, -m_thickness / 2.0, m_length, m_thickness);
    }
    else
    {
        return QRectF(-m_thickness / 2.0, 0, m_thickness, m_length);
    }
}

void CellSideGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    QPen pen(QBrush(m_color), m_thickness);
    painter->setPen(pen);
    painter->drawLine(_drawLinePos());
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->drawPoint(_drawLinePos().p1());
    painter->drawPoint(_drawLinePos().p2());
}

void CellSideGraphicsObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsObject::hoverEnterEvent(event);
    if (m_color != Qt::blue) {
        setColor(Qt::red);
    }
}

void CellSideGraphicsObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (m_color != Qt::blue) {
        setColor(Qt::black);
    }
    QGraphicsObject::hoverLeaveEvent(event);
}

void CellSideGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    setColor(Qt::gray);
    event->accept();
}

void CellSideGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setColor(Qt::blue);
    QGraphicsObject::mouseReleaseEvent(event);
}

QLineF CellSideGraphicsObject::_drawLinePos() const
{
    if (m_orientation == Qt::Horizontal)
    {
        return QLineF(0, 0, m_length, 0);
    }
    else
    {
        return QLineF(0, 0, 0, m_length);
    }
}
