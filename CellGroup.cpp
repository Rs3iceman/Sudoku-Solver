#include "CellGroup.h"
#include "Cell.h"

void CellGroup::SetCell(int index, Cell *cell)						//Takes in an integer and a cell pointer
{
	m_cells[index] = cell;										    //Sets the Cell Pointer parameter to point to the value of the index in the Cell Group
}
Cell* CellGroup::GetCellPointer(int index) const					//Takes an integer as a parameter
{
	Cell *cellPointer = m_cells[index];								//Initialises a new Cell Pointer and points it to the value of the index in the Cell Group
	return cellPointer;												//Returns the new cell pointer
}

CellGroup::CellGroup()
{
	for (int i = 0; i < 9; i++)
	{
		m_cells[i] = new Cell;										//Loops 9 times, adding a new Cell to the Cell Group each loop
	}
}

CellGroup::~CellGroup()
{
}
