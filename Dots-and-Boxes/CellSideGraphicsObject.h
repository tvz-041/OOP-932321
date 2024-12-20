#pragma once

#include <QGraphicsObject>

class CellSideGraphicsObject : public QGraphicsObject
{
    Q_OBJECT

public:
    CellSideGraphicsObject(int row, int column, Qt::Orientation orientation,
                           bool changeable = true, QGraphicsItem *parent = nullptr);

    int row() const;
    int column() const;
    Qt::Orientation orientation() const;

    /**
     * @brief Задаёт длину палочки в пикселях. Реальная длина будет (length + thickness * 2).
     */
    void setLength(int length);

    /**
     * @brief Задаёт толщину палочки в пикселях.
     */
    void setThickness(int thickness);
    void setColor(const QColor &color);

    /**
     * @brief Разрешает/запрещает изменение цвета палочки.
     */
    void setChangeable(bool changeable);
    void setOrientation(Qt::Orientation orientation);

    QRectF boundingRect() const override;

/**
 * Сигналы похожи на прототипы функций (т.е. просто объявили, а реализации нет).
 * В случае с обычными функциями объявление размещается в .h файле, а реализация в .cpp.
 * Компилятор сам связывает вызовы функций с их реализациями.
 *
 * С сигналами всё несколько иначе: своей реализации у них нет, но мы можем связывать их
 * (см connect в файле MainWindow.cpp) с реализацией слота. Ситуация похожа на ссылки -
 * можно сказать, что у нашего метода-слота появился ещё один "псевдоним", по которому
 * можно к нему обращаться. Теперь, если вызвать сигнал, будет вызываться связанный с ним слот.
 * Если связать один сигнал с несколькими слотами - все они будут вызываться.
 */
signals:
    void clicked(CellSideGraphicsObject* side);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int m_row = -1;
    int m_column = -1;
    int m_length = 5;
    int m_thickness = 1;
    Qt::Orientation m_orientation;
    bool m_changeable = true;
    QColor m_baseColor = Qt::black;
    QColor m_color;
};

