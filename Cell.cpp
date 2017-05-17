#include "Cell.h"
#include "SudokuPuzzle.h"
#include <vector>
#include <algorithm>

//Getters
int Cell::GetCoordinateAt(int index)
{
	return m_coordinates[index];							//Takes an integer as a parameter and returns one of the coordinates of the cell as an integer
}
const std::vector<int>* Cell::GetCandidateList() const
{
	return &m_candidateList;								//Returns the location of the Cells candidate list as a pointer to a vector
}
int Cell::GetCandidateListAt(int index)
{
	return m_candidateList[index];							//Takes an integer as a parameter and returns the value of the member in the candidate list at the index as an integer
}
int Cell::GetCandidateListSize() const 
{
	return m_candidateList.size();							//Returns the size of the cell's candidate list as an integer
}
int Cell::GetValue() const
{
	return m_value;											//Returns the value of the cell as an integer
}

//Setters
void Cell::SetCellValue(int activeValue)
{
	m_value = activeValue;									//Takes an integer as a parameter and sets the value of the cell equal to the integer parameter
}
void Cell::SetColumn(int column)
{
	m_coordinates[1] = column;								//Takes an integer as a parameter and sets the value of the 2nd coordinate equal to the integer parameter
}
void Cell::SetBlock(int block)
{
	m_coordinates[2] = block;								//Takes an integer as a parameter and sets the value of the 3rd coordinate equal to the integer parameter
}

//Used to remove Values from the candidate list
void Cell::RemoveFromCandidateList(int valueToRemove)
{
	m_candidateList.erase(std::remove(m_candidateList.begin(), m_candidateList.end(), valueToRemove), m_candidateList.end()); //https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
}



Cell::Cell(int value, bool given, int row) : m_value(value), m_given(given)
{
	m_coordinates[0] = row;									//Takes in 2 integers and a bool, sets the value and the 1st coordinate equal to the integers respectively, sets given equal to the bool
}


Cell::~Cell()
{
}
