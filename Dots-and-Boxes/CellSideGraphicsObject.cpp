#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "CellSideGraphicsObject.h"

CellSideGraphicsObject::CellSideGraphicsObject(int row, int column, Qt::Orientation orientation,
                                               bool changeable, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , m_row(row)
    , m_column(column)
    , m_orientation(orientation)
    , m_changeable(changeable)
{
    if (m_changeable)
    {
        m_baseColor = Qt::gray;
        // Разрешаем принимать события наведения мышкой (по умолчанию false)
        setAcceptHoverEvents(true);
        // Разрешаем принимать только нажатия ЛКМ (по умолчанию разрешены все)
        // (чтобы запретить всё, передать Qt::MouseButton::NoButton)
        setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
    }
    else
    {
        setAcceptedMouseButtons(Qt::MouseButton::NoButton);
        setZValue(1.0); // Внешние палочки должны отрисовываться поверх внутренних
    }
    m_color = m_baseColor;
}

int CellSideGraphicsObject::row() const
{
    return m_row;
}

int CellSideGraphicsObject::column() const
{
    return m_column;
}

Qt::Orientation CellSideGraphicsObject::orientation() const
{
    return m_orientation;
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

void CellSideGraphicsObject::setChangeable(bool changeable)
{
    m_changeable = changeable;
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
    pen.setColor(m_baseColor);
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
    if (m_changeable) {
        QColor color = m_baseColor;
        color.setAlphaF(0.70);
        setColor(color);
    }
}

void CellSideGraphicsObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (m_changeable) {
        setColor(m_baseColor);
    }
    QGraphicsObject::hoverLeaveEvent(event);
}

void CellSideGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    if (m_changeable) {
        QColor color = m_baseColor;
        color.setAlphaF(0.85);
        setColor(color);
    }
    event->accept();
}

void CellSideGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setColor(Qt::blue);
    QGraphicsObject::mouseReleaseEvent(event);
    emit clicked(this); // Вызов сигнала
}
