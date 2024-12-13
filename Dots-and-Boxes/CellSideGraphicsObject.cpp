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
    // Разрешаем принимать события наведения мышкой (по умолчанию false)
    setAcceptHoverEvents(true);
    // Разрешаем принимать только нажатия ЛКМ (по умолчанию разрешены все)
    // (чтобы запретить всё, передать Qt::MouseButton::NoButton)
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

/**
 * @brief Метод, возвращающий описывающий прямоугольник
 * (прямоугольник, внутри которого содержится весь наш объект).
 * Эта информация нужна для QGraphicsScene, чтобы она понимала,
 * какую область нужно перерисовывать, если у объекта сработал метод update().
 * В нашем случае палочка сама по себе есть прямоугольник, поэтому boundingRect()
 * полностью совпадает с реальными кабаритами.
 */
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
    // Рисуем саму линию в виде прямоугольника
    QPen pen(m_color);
    painter->setPen(pen);
    QRectF rect = boundingRect();
    painter->fillRect(rect, QBrush(m_color));

    // Палочки пересекаются на углах, поэтому для более красивого выделения
    // лучше покрасить в чёрный цвет начало и окончание палочки.
    // (можете закомментировать код ниже и посмотреть, что изменится).
    // Т.к. нам нужно закрасить квадрать, можно просто задать толщину ручки
    // и нарисовать точку в центре начала/окончания палочки.
    pen.setColor(Qt::black);
    pen.setWidth(m_thickness);
    painter->setPen(pen);
    // У QPointF есть операции +-, поэтому смещение можно задать так:
    QPointF offset = {m_thickness / 2.0, m_thickness / 2.0};
    painter->drawPoint(rect.topLeft() + offset);
    painter->drawPoint(rect.bottomRight() - offset);
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
    emit clicked(); // Вызов сигнала
}
