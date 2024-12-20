#include <QDebug>

#include "MapModel.h"

MapModel::MapModel(int rowCount, int columnCount)
    : m_cells(rowCount, std::vector<int>(columnCount, 0))
    , m_horizontalSides(rowCount + 1, std::vector<int>(columnCount, 0))
    , m_verticalSides(rowCount, std::vector<int>(columnCount + 1, 0))
{
    Q_ASSERT(rowCount > 1 && columnCount > 1);
    m_horizontalSides.front().assign(columnCount, -1);
    m_horizontalSides.back().assign(columnCount, -1);

    for (auto& sides : m_verticalSides) {
        sides.front() = sides.back() = -1;
    }
}

void MapModel::clear()
{
    for (int i = m_horizontalSides.size() - 2; i > 1; --i) {
        m_horizontalSides[i].assign(m_horizontalSides[i].size(), 0);
    }

    m_horizontalSides.front().assign(columnCount(), -1);
    m_horizontalSides.back().assign(columnCount(), -1);
    for (auto& sides : m_verticalSides) {
        sides.assign(sides.size(), 0);
        sides.front() = sides.back() = -1;
    }
}

int MapModel::horizontalSideOwner(int row, int column) const
{
    return m_horizontalSides[row][column];
}

int MapModel::verticalSideOwner(int row, int column) const
{
    return m_verticalSides[row][column];
}

int MapModel::cellOwner(int row, int column) const
{
    return m_cells[row][column];
}

int MapModel::rowCount() const
{
    return m_cells.size();
}

int MapModel::columnCount() const
{
    return rowCount() ? m_cells[0].size() : 0;
}

bool MapModel::setHorizontalSideOwner(int row, int column, int owner)
{
    if (owner <= 0 || !_isChangeableHorizontalSide(row, column)) {
        return false;
    }

    m_horizontalSides[row][column] = owner;
    _tryEncloseCell(row - 1, column, owner);
    _tryEncloseCell(row, column, owner);
    return true;
}

bool MapModel::setVerticalSideOwner(int row, int column, int owner)
{
    if (owner <= 0 || !_isChangeableVerticalSide(row, column)) {
        return false;
    }

    m_verticalSides[row][column] = owner;
    _tryEncloseCell(row, column - 1, owner);
    _tryEncloseCell(row, column, owner);
    return true;
}

bool MapModel::_isChangeableHorizontalSide(int row, int column) const
{
    return (
        (row > 0 && row < static_cast<int>(m_horizontalSides.size()) - 1) &&
        (column >= 0 && column < static_cast<int>(m_horizontalSides[row].size())) &&
        m_horizontalSides[row][column] == 0
    );
}

bool MapModel::_isChangeableVerticalSide(int row, int column) const
{
    return (
        (row >= 0 && row < static_cast<int>(m_verticalSides.size())) &&
        (column > 0 && column < static_cast<int>(m_verticalSides[row].size()) - 1) &&
        m_verticalSides[row][column] == 0
    );
}

bool MapModel::_tryEncloseCell(int row, int column, int owner)
{
    bool enclosed = m_horizontalSides[row][column] && m_horizontalSides[row + 1][column] &&
                    m_verticalSides[row][column] && m_verticalSides[row][column + 1];
    if (enclosed) {
        m_cells[row][column] = owner;
    }
    return enclosed;
}
