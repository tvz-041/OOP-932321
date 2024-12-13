#include <QDebug>

#include "CellSideGraphicsObject.h"

#include "MapWidget.h"

MapWidget::MapWidget(QWidget *parent)
    : QGraphicsView{parent}
    , m_model(10, 10)
    , m_scene(new QGraphicsScene(this))
{
    setScene(m_scene);
    clear();
}

void MapWidget::setVisible(bool visible)
{
    QGraphicsView::setVisible(visible);
    if (visible)
    {
        _updateSceneRect();
    }
}

void MapWidget::clear()
{
    m_scene->clear();
    m_model.clear();

    int offset = 0;
    int offsetDiff = m_cellSize + m_borderThickness;

    // Смещение по строкам - координата Y
    // Смещение по столбцам - координата X
    for (int row = 0; row < m_model.rowCount(); ++row)
    {
        for (int col = 0; col < m_model.columnCount(); ++col)
        {
            _addBorder(offset + offsetDiff * col, offset + offsetDiff * row, Qt::Horizontal);
        }

        for (int col = 0; col <= m_model.columnCount(); ++col)
        {
            _addBorder(offset + offsetDiff * col, offset + offsetDiff * row, Qt::Vertical);
        }
    }

    for (int col = 0; col < m_model.columnCount(); ++col)
    {
        _addBorder(offset + offsetDiff * col, offset + offsetDiff * m_model.rowCount(), Qt::Horizontal);
    }
}

void MapWidget::onCellSideClicked()
{
    qDebug() << "Cell side clicked!";
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    _updateSceneRect();
}

void MapWidget::_updateSceneRect()
{
    // Подгоняет размер сцены под размер видимой части.
    // Будет полезно для автомасштабирования, пока не требуется.
#if 0
    m_scene->setSceneRect(QRect(
        0, 0,
        viewport()->width(),
        viewport()->height()
    ));
#endif
}

void MapWidget::_addBorder(int x, int y, Qt::Orientation type)
{
    CellSideGraphicsObject *border = new CellSideGraphicsObject(type);
    border->setLength(m_cellSize);
    border->setThickness(m_borderThickness);
    border->setPos(x, y);
    m_scene->addItem(border);
}
