#pragma once

#include <vector>

/**
 * @brief Модель игровой карты.
 * С точки зрения модели достаточно хранить информацию о том,
 * какая палочка/ячейка кому принадлежит:
 * -1: внешняя граница (не может принадлежать никому);
 * 0: пока никому не принадлежит;
 * 1: принадлежит игроку №1;
 * 2: принадлежит игроку №2;
 * и т.д.
 */
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
     * @brief Меняет владельца горизонтальной палочки, если это допустимо
     * (текущего владельца нет и его в принципе можно задать для этой палочки).
     * Возвращает количество ячеек, захваченных в результате закраса палочки.
     */
    int setHorizontalSideOwner(int row, int column, int owner);

    /**
     * @brief Меняет владельца вертикальной палочки, если это допустимо
     * (текущего владельца нет и его в принципе можно задать для этой палочки).
     * Возвращает количество ячеек, захваченных в результате закраса палочки.
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

