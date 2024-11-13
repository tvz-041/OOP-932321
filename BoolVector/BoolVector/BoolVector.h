#pragma once

class BoolVector
{
public:
    class Rank;
    
public:
    using Cell = unsigned char;
    static const int CellSize = 8; // sizeof(Cell) * 8
    BoolVector(int length = CellSize);
    BoolVector(int length, bool value); // TODO: implement
    BoolVector(const BoolVector& other);
    ~BoolVector();
    
    int length() const;
    
    void swap(BoolVector& other); 
    bool bitValue(int index) const;
    void setBitValue(int index, bool value);
    
    BoolVector& operator=(const BoolVector& other);
    Rank operator[](int index);
    
private:
    int _excessRankCount() const;
    static Cell _mask(int index);

private:
    Cell* m_cells = nullptr;
    int m_cellCount = 0;
    int m_length = 0;
};

class BoolVector::Rank
{
public:
    Rank() = default;
    Rank(Cell* cell, Cell mask);
    Rank& operator=(const Rank& other);
    Rank& operator=(bool value);
    operator bool() const;
    
private:
    Cell* m_cell = nullptr;
    Cell m_mask = 0;
};
