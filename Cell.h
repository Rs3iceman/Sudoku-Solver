#include <vector>
#pragma once

class Cell
{
public:
	Cell(void) : m_value(NULL), m_given(NULL) {}
	Cell(int value, bool given, int row);
	~Cell(void);

	const std::vector<int>* GetCandidateList() const;
	int GetCoordinateAt(int index);
	int GetCandidateListAt(int index);
	int GetValue() const;
	int GetCandidateListSize() const;

	void SetCellValue(int activeValue);
	void SetBlock(int block);
	void SetColumn(int column);

	void RemoveFromCandidateList(int valueToRemove);
private:
	std::vector<int> m_candidateList{ 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;					//Initialises a vector with 9 members
	std::vector<int> m_coordinates{ 0, 0, 0 };										//Initialises a vector with 3 members
	int m_value;																	//Reserves space in memory for an integer member variable
	bool m_given = false;															//Initialises a bool member variable and sets it to false

};

