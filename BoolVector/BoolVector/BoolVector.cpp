#include <assert.h>
#include <utility>

#include "BoolVector.h"

BoolVector::BoolVector(int length)
	: m_length(length)
{
	// TODO: length check (>= 0)
	m_cellCount = m_length / CellSize;
	if (m_length % CellSize != 0)
	{
		m_cellCount++;
	}

	m_cells = new Cell[m_cellCount];
}

BoolVector::BoolVector(const BoolVector& other)
{
    m_cellCount = other.m_cellCount;
    m_length = other.m_length;
    m_cells = new Cell[m_cellCount];
    for(int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] = other.m_cells[i];
    }
}

BoolVector::~BoolVector()
{
	delete[] m_cells;
}

int BoolVector::length() const
{
	return m_length;
}

void BoolVector::swap(BoolVector& other)
{
	std::swap(m_cells, other.m_cells);
	std::swap(m_cellCount, other.m_cellCount);
	std::swap(m_length, other.m_length);
}

bool BoolVector::bitValue(int index) const
{
	assert(index >= 0 && index < m_length);
	Cell mask = _mask(index);
	return m_cells[index / CellSize] & mask;
}

void BoolVector::setBitValue(int index, bool value)
{
	assert(index >= 0 && index < m_length);
	Cell mask = _mask(index);
	if (value)
	{
		m_cells[index / CellSize] |= mask;
	}
	else
	{
		m_cells[index / CellSize] &= ~mask;
	}
}

BoolVector& BoolVector::operator=(const BoolVector& other)
{
	return *this;
}

BoolVector::Rank BoolVector::operator[](int index)
{
	assert(index >= 0 && index < m_length);
    return Rank(&m_cells[index / CellSize], _mask(index));
}

int BoolVector::_excessRankCount() const
{
	return (m_cellCount * CellSize - m_length);
}

BoolVector::Cell BoolVector::_mask(int index)
{
    Cell mask = 1;
	mask <<= CellSize - 1 - (index % CellSize);
	return mask;
}

BoolVector::Rank::Rank(Cell* cell, Cell mask)
    : m_cell(cell)
    , m_mask(mask)
{
    assert(m_cell != nullptr);
    assert(m_mask > 0);
}

BoolVector::Rank& BoolVector::Rank::operator=(const Rank& other)
{
    return operator=(static_cast<bool>(other));
}

BoolVector::Rank& BoolVector::Rank::operator=(bool value)
{
    if (value)
    {
        *m_cell |= m_mask;
    }
    else
    {
        *m_cell &= ~m_mask;
    }
    return *this;
}

BoolVector::Rank::operator bool() const
{
	return (*m_cell & m_mask) != 0;
}
