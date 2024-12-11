#pragma once

#include <vector>

class MapModel
{
public:
    MapModel(int rowCount, int columnCount);
    ~MapModel() = default;

    void clear();

    int horizontalSideOwner(int row, int column) const;
    int verticalSideOwner(int row, int column) const;
    int cellOwner(int row, int column) const;

    int rowCount() const;
    int columnCount() const;

    /**
     * @brief setHorizontalSideOwner
     * @param row
     * @param column
     * @param owner
     * @return count of captured cells
     */
    int setHorizontalSideOwner(int row, int column, int owner);

    /**
     * @brief setVerticalSideOwner
     * @param row
     * @param column
     * @param owner
     * @return count of captured cells
     */
    int setVerticalSideOwner(int row, int column, int owner);

private:
    bool _isChangeableHorizontalSide(int row, int column) const;
    bool _isChangeableVerticalSide(int row, int column) const;
    bool _tryEncloseCell(int row, int column, int owner);

private:
    std::vector<std::vector<int>> m_cells;
    std::vector<std::vector<int>> m_horizontalSides;
    std::vector<std::vector<int>> m_verticalSides;
};

