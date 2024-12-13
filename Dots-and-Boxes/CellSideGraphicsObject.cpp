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
        return QRectF(0, 0, m_length + m_thickness * 2, m_thickness);
    }
    else
    {
        return QRectF(0, 0, m_thickness, m_length + m_thickness * 2);
    }
}

void CellSideGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    QPen pen(m_color);
    painter->setPen(pen);
    painter->fillRect(boundingRect(), QBrush(m_color));

    pen.setColor(Qt::black);
    pen.setWidth(m_thickness);
    painter->setPen(pen);
    painter->drawPoint(
        boundingRect().left() + m_thickness / 2.0,
        boundingRect().top() + m_thickness / 2.0
    );
    painter->drawPoint(
        boundingRect().right() - m_thickness / 2.0,
        boundingRect().bottom() - m_thickness / 2.0
    );
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
