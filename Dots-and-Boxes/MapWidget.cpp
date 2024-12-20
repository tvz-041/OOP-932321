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
        _updateView();
    }
}

QColor MapWidget::playerColor(int player)
{
    switch (player)
    {
        case 1: return Qt::red;
        case 2: return Qt::blue;
        default: return Qt::gray;
    }
}

QString MapWidget::playerColorString(int player)
{
    switch (player)
    {
        case 1: return tr("Red");
        case 2: return tr("Blue");
        default: return tr("Unknown");
    }
}

QColor MapWidget::currentPlayerColor() const
{
    return playerColor(m_currentPlayer);
}

void MapWidget::setCurrentPlayer(int player)
{
    m_currentPlayer = player;
}

void MapWidget::clear()
{
    m_scene->clear();
    m_model.clear();

    // Смещение по строкам - координата Y
    // Смещение по столбцам - координата X
    for (int row = 0; row < m_model.rowCount(); ++row)
    {
        for (int col = 0; col < m_model.columnCount(); ++col)
        {
            _addBorder(row, col, Qt::Horizontal);
        }

        for (int col = 0; col <= m_model.columnCount(); ++col)
        {
            _addBorder(row, col, Qt::Vertical);
        }
    }

    for (int col = 0; col < m_model.columnCount(); ++col)
    {
        _addBorder(m_model.rowCount(), col, Qt::Horizontal);
    }
}

void MapWidget::onCellSideClicked(CellSideGraphicsObject* side)
{
    bool isSideCaptured = false;

    /*
     * При захвате палочки может быть захвачено до двух ячеек:
     * - верхняя/нижняя, если палочка горизонтальная;
     * - левая/правая, если палочка вертикальная;
     * Эти ячейки назовём "first" и "second" соответственно.
     * Верхняя и левая ячейки расположены сверху или слева от палочки,
     * поэтому одна из координат (индекс строки/столбца)
     * будет на единицу меньше.
     */
    int firstCellRow = side->row();
    int firstCellColumn = side->column();
    int secondCellRow = side->row();
    int secondCellColumn = side->column();

    if (side->orientation() == Qt::Horizontal)
    {
        isSideCaptured = m_model.setHorizontalSideOwner(side->row(), side->column(), m_currentPlayer);
        firstCellRow -= 1;
    }
    else
    {
        isSideCaptured = m_model.setVerticalSideOwner(side->row(), side->column(), m_currentPlayer);
        firstCellColumn -= 1;
    }

    if (!isSideCaptured)
    {
        return;
    }

    side->setColor(currentPlayerColor());
    // TODO: запрет изменения палочки

    if (m_model.cellOwner(firstCellRow, firstCellColumn) > 0)
    {
        _paintCell(firstCellRow, firstCellColumn);
    }

    if (m_model.cellOwner(secondCellRow, secondCellColumn) > 0)
    {
        _paintCell(secondCellRow, secondCellColumn);
    }
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    _updateView();
}

void MapWidget::_updateView()
{
    int width = (m_cellSize + m_borderThickness) * m_model.columnCount() + m_borderThickness;
    int height = (m_cellSize + m_borderThickness) * m_model.rowCount() + m_borderThickness;
    fitInView(QRectF(0, 0, width, height), Qt::KeepAspectRatio);
}

void MapWidget::_addBorder(int row, int col, Qt::Orientation type)
{
    bool changeable;
    if (type == Qt::Horizontal)
    {

        changeable = (m_model.horizontalSideOwner(row, col) != -1);
    }
    else
    {
        changeable = (m_model.verticalSideOwner(row, col) != -1);
    }

    CellSideGraphicsObject *border = new CellSideGraphicsObject(row, col, type, changeable);
    if (changeable) // Нет смысла ждать сигналов от неизменяемых палочек
    {
        // TODO: connect палочки и виджета
    }

    int x = col * (m_cellSize + m_borderThickness);
    int y = row * (m_cellSize + m_borderThickness);
    border->setPos(x, y);
    border->setLength(m_cellSize);
    border->setThickness(m_borderThickness);

    m_scene->addItem(border);
}

void MapWidget::_paintCell(int row, int col)
{
    qreal left = col * (m_cellSize + m_borderThickness) + m_borderThickness;
    qreal right = left + m_cellSize;
    qreal top = row * (m_cellSize + m_borderThickness)  + m_borderThickness;
    qreal bottom = top + m_cellSize;

    QPen pen(currentPlayerColor(), m_borderThickness / 2);
    m_scene->addLine(left, top, right, bottom, pen)->setZValue(-1);
    m_scene->addLine(right, top, left, bottom, pen)->setZValue(-1);
}
