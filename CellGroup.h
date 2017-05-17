#pragma once
#include "Cell.h"

class CellGroup
{
public:
	CellGroup();
	~CellGroup(void);

	void SetCell(int index, Cell *cell);
	Cell* GetCellPointer(int index) const;

private:
	Cell* m_cells[9];									//Reserves space in memory for an array of 9 cell pointers
};

