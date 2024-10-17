#include <assert.h>

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

BoolVector::BoolVector(int length, bool value)
	: BoolVector(length)
{
	// TODO: implement
}

BoolVector::~BoolVector()
{
	delete[] m_cells;
}

bool BoolVector::bitValue(int index) const
{
	assert(index >= 0 && index < m_length);
	Cell mask = 1;
	mask <<= CellSize - (index % CellSize);
	return m_cells[index / CellSize] & mask;
}

void BoolVector::setBitValue(int index, bool value)
{
	assert(index >= 0 && index < m_length);
	Cell mask = 1;
	mask <<= CellSize - (index % CellSize);
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
	// TODO: implement
	return *this;
}

//bool BoolVector::operator[](int index)
//{

//}

int BoolVector::_excessRankCount() const
{
	return (m_cellCount * CellSize - m_length);
}
