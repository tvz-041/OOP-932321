#include <QDebug>

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
    m_sides.clear();
    m_scene->clear();
    m_model.clear();

    int offset = m_borderThickness / 2.0;

    for (int y = 0; y < m_model.rowCount(); ++y)
    {
        for (int x = 0; x < m_model.columnCount(); ++x)
        {
            _addBorder(offset + m_cellSize * x, offset + m_cellSize * y, Qt::Horizontal);
        }

        for (int x = 0; x <= m_model.columnCount(); ++x)
        {
            _addBorder(offset + m_cellSize * x, offset + m_cellSize * y, Qt::Vertical);
        }
    }

    for (int x = 0; x < m_model.columnCount(); ++x)
    {
        _addBorder(offset + m_cellSize * x, offset + m_cellSize * m_model.rowCount(), Qt::Horizontal);
    }
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    _updateSceneRect();
}

void MapWidget::_updateSceneRect()
{
    m_scene->setSceneRect(QRect(
        0, 0,
        viewport()->width(),
        viewport()->height()
    ));
}

void MapWidget::_addBorder(int x, int y, Qt::Orientation type)
{
    CellSideGraphicsObject *border = new CellSideGraphicsObject(type);
    border->setLength(m_cellSize);
    border->setThickness(m_borderThickness);
    border->setPos(x, y);
    m_scene->addItem(border);
}
