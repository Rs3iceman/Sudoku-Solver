#include "SudokuPuzzle.h"
#include <Windows.h>
#include "Cell.h"
#include "CellGroup.h"
#include <vector>
#include <algorithm>

SudokuPuzzle::~SudokuPuzzle(void)
{
}
void SudokuPuzzle::InitialiseGrid(char filenameIn[])
{
	bool given = false;																					//Initialise a bool member variable and set its value to false
	Cell *temp;																							//Reserve space in memory for a cell pointer variable
	int addedBlockValue = 0;																			//Initialise a integer variable and set its value to 0
	int addedColumnValue = 0;																			//Initialise a integer variable and set its value to 0
	int addedRowValue = 0;																				//Initialise a integer variable and set its value to 0
	ifstream fin(filenameIn);																			//Opens an input stream to the input file
	if (fin.is_open())																					//checks if the input stream is open
	{
		int c = 0;																						//Initialise a integer variable and set its value to 0
		for (int row = 0; row < 9; ++row)																//Loops through every row
		{
			for (int column = 0; column < 9; ++column)													//Loops through every column
			{
				fin >> c;																				//inputs one integer from the input stream
				if (c != 0)																				//checks if the inputted value is 0
				{
					given = true;																		//If the value isn't 0, given is set to true
				}
				else
				{
					given = false;																		//Else given is set to false
				}
				m_gridRows[row].SetCell(column, new Cell(c, given, row));								//Calls the SetCell function on the Cell at position row in the CellGroup m_gridrows, with 2 integers and a bool
			}
		}
	}
	for (int column = 0; column < 9; ++column)															//Loops through every column
	{	
		for (int row = 0; row < 9; ++row)																//Loops through every row
		{
			temp = m_gridRows[row].GetCellPointer(column);												//Calls the GetCellPointer function on the Cell at position row in the CellGroup m_gridrows with the column integer and sets the value of temp to the result
			m_gridColumns[column].SetCell(row, temp);													//Calls the SetCell function on the Cell at position column in the CellGroup m_gridcolumns with the row integer and the temp cell pointer
			temp->SetColumn(column);																	//Calls the Cell function SetColumn on the temp cell pointer with the column integer
		}
	}
	for (int block = 0; block < 9; ++block)																//Loops through every block
	{
		for (int row = 0; row < 3; ++row)																//Loops through the first 3 values in each row
		{
			if (row == 1)																				//Checks if row is on the second loop
			{
				addedColumnValue = 3;																	//If true, sets the value of addedColumnValue to 3, used later to reach the 4th, 5th and 6th value in the row
			}
			if (row == 2)																				//Checks if row is on the third loop
			{
				addedColumnValue = 6;																	//If true, sets the value of addedColumnValue to 6, used later to reach the 7th, 8th and 9th value in the row
			}
			for (int column = 0; column < 3; ++column)													//Loops through the first 3 values in each column
			{
				temp = m_gridRows[row + addedRowValue].GetCellPointer(column + addedBlockValue);		//Calls the GetCellPointer function on the Cell at position of the row added to the addedRowValue in the CellGroup m_gridrows with the column integer added to the addedBlockValue integer and sets the value of temp to the result
				m_gridBlocks[block].SetCell(column + addedColumnValue, temp);							//Calls the SetCell function on the Cell at position block in the CellGroup m_gridBlocks with the column integer added to the addedColumnValue integer and the temp cell pointer
				temp->SetBlock(block);																	//Calls the Cell function SetBlock on the temp cell pointer with the block integer
			}
		}
		addedColumnValue = 0;																			//Sets the addedColumnValue integer to 0
		if (addedBlockValue == 6)																		//Checks if the addedBlockValue is 6
		{
			addedBlockValue = 0;																		//Sets addedBlockValue to 0
			addedRowValue += 3;																			//Iterates addedRowValue by 3
		}
		else
		{
			addedBlockValue += 3;																		//Else iterates addedBlockValue by 3
		}
	}
}

void SudokuPuzzle::CandidateListInitialiser() const
{
	for (int cellGroup = 0; cellGroup < 9; ++cellGroup)													//Loops through every Row
	{
		for (int cellLocation = 0; cellLocation < 9; ++cellLocation)									//Loops through every cell
		{
			for (int activeValue = 1; activeValue < 10; ++activeValue)									//Loops through every possible value
			{
				for (int comparableCell = 0; comparableCell < 9; ++comparableCell)						//Loops through every comparable cell
				{
					CandidateListRowUpdater(cellGroup, cellLocation, activeValue, comparableCell);		//Calls CandidateListRowUpdater with the active row, cell, value and comparable cell
					CandidateListColumnUpdater(cellGroup, cellLocation, activeValue, comparableCell);	//Calls CandidateListColumnUpdater with the active row, cell, value and comparable cell
					CandidateListBlockUpdater(cellGroup, cellLocation, activeValue, comparableCell);	//Calls CandidateListBlockUpdater with the active row, cell, value and comparable cell
				}
			}
		}
	}
}
void SudokuPuzzle::CandidateListRowUpdater(int cellGroup, int cellLocation, int activeValue, int comparableCell) const
{
	Cell *cell = m_gridRows[cellGroup].GetCellPointer(cellLocation);									//Calls the GetCellPointer function on the Cell at position cellLocation in the CellGroup m_gridrows and points the "cell" cell pointer to the result
	if (cell->GetValue() == 0)																			//Calls the GetValue function on the cell to check if its value equals 0
	{
		if (cellLocation != comparableCell)																//Checks the active cell is not equal to the comparable cell
		{
			Cell *comparableCellPointer = m_gridRows[cellGroup].GetCellPointer(comparableCell);			//Calls the GetCellPointer function on the Cell at position comparableCell in the CellGroup m_gridrows and points the "comparableCellPointer" cell pointer to the result
			int comparableCellValue = comparableCellPointer->GetValue();								//Calls the Cell function GetValue on the comparableCellPointer and sets the comparableCellValue integer to the result
			if (activeValue == comparableCellValue)														//Checks if the active value is equal to the comparableCell's Value
			{
				cell->RemoveFromCandidateList(activeValue);												//If true, calls the RemoveFromCandidateList Cell function, on the "cell" cell pointer with the activeValue 
			}
		}
	}
}
void SudokuPuzzle::CandidateListColumnUpdater(int cellGroup, int cellLocation, int activeValue, int comparableCell) const
{
	Cell *cell = m_gridColumns[cellGroup].GetCellPointer(cellLocation);									//Calls the GetCellPointer function on the Cell at position cellLocation in the CellGroup m_gridColumns and points the "cell" cell pointer to the result
	if (cell->GetValue() == 0)																			//Calls the GetValue function on the cell to check if its value equals 0
	{
		if (cellLocation != comparableCell)																//Checks the active cell is not equal to the comparable cell
		{
			Cell *comparableCellPointer = m_gridColumns[cellGroup].GetCellPointer(comparableCell);		//Calls the GetCellPointer function on the Cell at position comparableCell in the CellGroup m_gridColumns and points the "comparableCellPointer" cell pointer to the result
			int comparableCellValue = comparableCellPointer->GetValue();								//Calls the Cell function GetValue on the comparableCellPointer and sets the comparableCellValue integer to the result
			if (activeValue == comparableCellValue)														//Checks if the active value is equal to the comparableCell's Value
			{
				cell->RemoveFromCandidateList(activeValue);												//If true, calls the RemoveFromCandidateList Cell function, on the "cell" cell pointer with the activeValue 
			}
		}
	}
}
void SudokuPuzzle::CandidateListBlockUpdater(int cellGroup, int cellLocation, int activeValue, int comparableCell) const
{
	Cell *cell = m_gridBlocks[cellGroup].GetCellPointer(cellLocation);									//Calls the GetCellPointer function on the Cell at position cellLocation in the CellGroup m_gridColumns and points the "cell" cell pointer to the result
	if (cell->GetValue() == 0)																			//Calls the GetValue function on the cell to check if its value equals 0
	{
		if (cellLocation != comparableCell)																//Checks the active cell is not equal to the comparable cell
		{
			Cell *comparableCellPointer = m_gridBlocks[cellGroup].GetCellPointer(comparableCell);		//Calls the GetCellPointer function on the Cell at position comparableCell in the CellGroup m_gridColumns and points the "comparableCellPointer" cell pointer to the result
			int comparableCellValue = comparableCellPointer->GetValue();								//Calls the Cell function GetValue on the comparableCellPointer and sets the comparableCellValue integer to the result
			if (activeValue == comparableCellValue)														//Checks if the active value is equal to the comparableCell's Value
			{
				cell->RemoveFromCandidateList(activeValue);												//If true, calls the RemoveFromCandidateList Cell function, on the "cell" cell pointer with the activeValue 
			}
		}
	}
}

void SudokuPuzzle::SolveLoop()
{
	Cell *cell;																							//Reserves a spave in memory for a cell pointer called cell
	while (!solved)																						//loops while solved isn't true
	{
		for (int cellGroup = 0; cellGroup < 9; ++cellGroup)												//loops through every cell group
		{
			for (int cellLocation = 0; cellLocation < 9; ++cellLocation)								//loops through every cell
			{
				cell = m_gridRows[cellGroup].GetCellPointer(cellLocation);								//Calls the GetCellPointer function on the Cell at position cellLocation in the CellGroup m_gridRows and points the "cell" cell pointer to the result
				if (cell->GetValue() == 0)																//Calls the GetValue function on the cell to check if its value equals 0
				{
					if (!NakedSingle(cell))																//Calls NakedSingle with the cell and checks if it succeeds in setting a value
					{
						HiddenSingle(cell);																//If NakedSingle fails then HiddenSingle is called with the cell
					}
				}
			}
		}
		if (solvedCells == oldSolvedCells)																//Checks if any cells were solved after one pass
		{
			solved = true;																				//If true, sets solved equal to true
		}
		oldSolvedCells = solvedCells;																	//Sets the new amount of oldSolvedCells for the next loop
		IncrementPasses();																				//Calls the IncrementPasses function to increment the amount of passes performed
	}
}
bool SudokuPuzzle::NakedSingle(Cell *cell)
{
	if (cell->GetCandidateListSize() == 1)																//Calls the GetCandidateListSize Cell function on the cell and checks if its candidate list only contains 1 value
	{
		int cellValue = cell->GetCandidateListAt(0);													//If true, Calls the GetCandidateListAt Cell function on the cell with 0, getting the 1st member of the candidate list and setting the cellValue variable to the result
		IncrementSolvedCells();																			//Calls the IncrementSolvedCells function to increment the total amount of solved cells
		IncrementSolvedNakedSingleCells();																//Calls the IncrementSolvedNakedSingleCells function to increment the  amount of cells solved using Naked Single
		cell->SetCellValue(cellValue);																	//Calls the SetCellValue Cell function on the cell with the cellValue, setting the value of cell
		CandidateListUpdater(cell);																		//Calls the CandidateListUpdater function with the cell
		return true;
	}
	else { return false; };
}
bool SudokuPuzzle::HiddenSingle(Cell *cell)
{
	if (!HiddenRowLoop(cell))																			//Calls the HiddenRowLoop function with the "cell" cell pointer and it is checked to see if it succeeds
	{
		if (!HiddenColumnLoop(cell))																	//If the prevous function doesn't succeed, HiddenColumnLoop is called with the "cell" cell pointer and it is checked to see if it succeeds
		{
			if (!HiddenBlockLoop(cell))																	//If the prevous function doesn't succeed, HiddenBlockLoop is called with the "cell" cell pointer and it is checked to see if it succeeds
			{
				return false;																			//If all Loops fail, false is returned by the function
			}
		}
	}
	return true;
}
bool SudokuPuzzle::HiddenRowLoop(Cell *cell)
{
	int candidateListSize = cell->GetCandidateListSize();												//Calls the Cell function GetCandidateListSize on the "cell" cell pointer, initialises a integer variable called CandidateListSize and sets its value equal to the function result
	std::vector<int> tempCandidateList = *cell->GetCandidateList();										//Calls the Cell function GetCandidateList on the "cell" cell pointer, initialises a vector called tempCandidateList and sets it to the candidatelist acquired from the function call
	int row = cell->GetCoordinateAt(0);																	//Calls the Cell function GetCoordinateAt on the "cell" cell pointer with the value 0, initialises a integer variable called row and sets its value equal to the function result
	Cell *comparableCell;																				//Reserves space in memory for a Cell pointer

	for (int x = 0; x < candidateListSize; ++x)															//Loops through the candidate list
	{
		int value = cell->GetCandidateListAt(x);														//Calls the GetCandidateListAt Cell function with the x variable, initalises a integer called value and sets its value equal to the function result
		IncrementConsidered();

		for (int comparableCellLocation = 0; comparableCellLocation < 9; ++comparableCellLocation)		//Loops through the comparable cells
		{
			if (comparableCellLocation != row)															//Checks if the comparable cell is not the active cell
			{
				comparableCell = m_gridRows[row].GetCellPointer(comparableCellLocation);				//Calls the GetCellPointer function on the Cell at position comparableCellLocation in the CellGroup m_gridRows and points the "comparableCell" cell pointer to the result
				if (comparableCell->GetValue() == 0)													//Calls the GetValue Cell function on the comparableCell and checks if the value is equal to 0
				{
					HiddenComparableCandidateListLoop(comparableCell, value, tempCandidateList);		//If true, the HiddenComparableCandidateListLoop function is called with the comparableCell, the active value and the tempCandidateList
				}
			}
		}
	}
	if (HiddenCandidateListChecker(cell, tempCandidateList))											//Calls HiddenCandidateListChecker with the cell and the tempCandidateList to check if the CandidateList of the cell contains 1 value
	{
		return true;
	}
	else return false;
}
bool SudokuPuzzle::HiddenColumnLoop(Cell *cell)
{
	int candidateListSize = cell->GetCandidateListSize();												//Calls the Cell function GetCandidateListSize on the "cell" cell pointer, initialises a integer variable called CandidateListSize and sets its value equal to the function result
	std::vector<int> tempCandidateList = *cell->GetCandidateList();										//Calls the Cell function GetCandidateList on the "cell" cell pointer, initialises a vector called tempCandidateList and sets it to the candidatelist acquired from the function call
	int column = cell->GetCoordinateAt(1);																//Calls the Cell function GetCoordinateAt on the "cell" cell pointer with the value 1, initialises a integer variable called column and sets its value equal to the function result
	Cell *comparableCell;																				//Reserves space in memory for a Cell pointer

	for (int x = 0; x < candidateListSize; ++x)															//Loops through the candidate list
	{
		int value = cell->GetCandidateListAt(x);														//Calls the GetCandidateListAt Cell function with the x variable, initalises a integer called value and sets its value equal to the function result
		IncrementConsidered();

		for (int comparableCellLocation = 0; comparableCellLocation < 9; ++comparableCellLocation)		//Loops through the comparable cells
		{
			if (comparableCellLocation != column)														//Checks if the comparable cell is not the active cell
			{
				comparableCell = m_gridColumns[column].GetCellPointer(comparableCellLocation);			//Calls the GetCellPointer function on the Cell at position comparableCellLocation in the CellGroup m_gridColumns and points the "comparableCell" cell pointer to the result
				if (comparableCell->GetValue() == 0)													//Calls the GetValue Cell function on the comparableCell and checks if the value is equal to 0
				{
					HiddenComparableCandidateListLoop(comparableCell, value, tempCandidateList);		//If true, the HiddenComparableCandidateListLoop function is called with the comparableCell, the active value and the tempCandidateList
				}
			}
		}
	}
	if (HiddenCandidateListChecker(cell, tempCandidateList))											//Calls HiddenCandidateListChecker with the cell and the tempCandidateList to check if the CandidateList of the cell contains 1 value
	{
		return true;
	}
	else return false;
}
bool SudokuPuzzle::HiddenBlockLoop(Cell *cell)
{
	int candidateListSize = cell->GetCandidateListSize();												//Calls the Cell function GetCandidateListSize on the "cell" cell pointer, initialises a integer variable called CandidateListSize and sets its value equal to the function result
	std::vector<int> tempCandidateList = *cell->GetCandidateList();										//Calls the Cell function GetCandidateList on the "cell" cell pointer, initialises a vector called tempCandidateList and sets it to the candidatelist acquired from the function call
	int block = cell->GetCoordinateAt(2);																//Calls the Cell function GetCoordinateAt on the "cell" cell pointer with the value 2, initialises a integer variable called block and sets its value equal to the function result
	Cell *comparableCell;																				//Reserves space in memory for a Cell pointer

	for (int x = 0; x < candidateListSize; ++x)															//Loops through the candidate list
	{
		int value = cell->GetCandidateListAt(x);														//Calls the GetCandidateListAt Cell function with the x variable, initalises a integer called value and sets its value equal to the function result
		IncrementConsidered();

		for (int comparableCellLocation = 0; comparableCellLocation < 9; ++comparableCellLocation)		//Loops through the comparable cells
		{
			if (comparableCellLocation != block)														//Checks if the comparable cell is not the active cell
			{
				comparableCell = m_gridBlocks[block].GetCellPointer(comparableCellLocation);			//Calls the GetCellPointer function on the Cell at position comparableCellLocation in the CellGroup m_gridBlocks and points the "comparableCell" cell pointer to the result
				if (comparableCell->GetValue() == 0)													//Calls the GetValue Cell function on the comparableCell and checks if the value is equal to 0
				{
					HiddenComparableCandidateListLoop(comparableCell, value, tempCandidateList);		//If true, the HiddenComparableCandidateListLoop function is called with the comparableCell, the active value and the tempCandidateList
				}
			}
		}
	}
	if (HiddenCandidateListChecker(cell, tempCandidateList))											//Calls HiddenCandidateListChecker with the cell and the tempCandidateList to check if the CandidateList of the cell contains 1 value
	{
		return true;
	}
	else return false;
}
void SudokuPuzzle::HiddenComparableCandidateListLoop(Cell *comparableCell, int value, std::vector<int> &tempCandidateList) const
{
	int comparableValue;																				//Reserves space in memory for an integer
	int comparableCandidateListSize = comparableCell->GetCandidateListSize();							//Calls the Cell function GetCandidateListSize on the "comparableCell" cell pointer, initialises a integer variable called comparableCandidateListSize and sets its value equal to the function result
	for (int y = 0; y < comparableCandidateListSize; ++y)												//Loops through the comparable candidate list
	{
		comparableValue = comparableCell->GetCandidateListAt(y);										//Calls the GetCandidateListAt Cell function with the y variable, initalises a integer called comparableValue and sets its value equal to the function result
		if (value == comparableValue)																	//Checks if the active value is equal to the comparable value
		{
			tempCandidateList.erase(std::remove(tempCandidateList.begin(), tempCandidateList.end(), value), tempCandidateList.end());	//https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
		}
	}
}
bool SudokuPuzzle::HiddenCandidateListChecker(Cell *cell, std::vector<int> &tempCandidateList)
{
	if (tempCandidateList.size() == 1)																	//Calls the size function on the tempCandidatelist to find the size of the vector then checks if it is equal to 1 
	{
		cell->SetCellValue(tempCandidateList[0]);														//If true, the SetCellValue Cell function is called on the cell with the first member of the tempCandidateList
		IncrementSolvedCells();																			//Calls the IncrementSolvedCells function to increment the total amount of solved cells
		IncrementSolvedHiddenSingleCells();																//Calls the IncrementSolvedHiddenSingleCells function to increment the  amount of cells solved using Hidden Single
		CandidateListUpdater(cell);																		//Calls the CandidateListUpdater function with the cell
		return true;
	}
	else return false;
}
void SudokuPuzzle::CandidateListUpdater(Cell *cell) const
{
	int updatingValue = cell->GetValue();																//Calls the Cell function GetValue on the cell and sets the updatingValue integer to the result
	int row = cell->GetCoordinateAt(0);																	//Calls the Cell function GetCoordinateAt on the "cell" cell pointer with the value 0, initialises a integer variable called row and sets its value equal to the function result
	int column = cell->GetCoordinateAt(1);																//Calls the Cell function GetCoordinateAt on the "cell" cell pointer with the value 1, initialises a integer variable called column and sets its value equal to the function result
	int block = cell->GetCoordinateAt(2);																//Calls the Cell function GetCoordinateAt on the "cell" cell pointer with the value 2, initialises a integer variable called block and sets its value equal to the function result
	Cell *updatingCell;																					//Reserves space in memory for a Cell pointer
	for (int updatingCellLocation = 0; updatingCellLocation < 9; ++updatingCellLocation)				//Loops through the updatingCells
	{
		updatingCell = m_gridRows[row].GetCellPointer(updatingCellLocation);							//Calls the GetCellPointer function on the Cell at position row in the CellGroup m_gridRows with the updatingCellLocation integer and points the "updatingCell" Cell Pointer to the result
		updatingCell->RemoveFromCandidateList(updatingValue);											//Calls the RemoveFromCandidateList function on the "updatingCell" Cell Pointer with the updatingValue Integer
		updatingCell = m_gridColumns[column].GetCellPointer(updatingCellLocation);						//Calls the GetCellPointer function on the Cell at position column in the CellGroup m_gridColumns with the updatingCellLocation integer and points the "updatingCell" Cell Pointer to the result
		updatingCell->RemoveFromCandidateList(updatingValue);											//Calls the RemoveFromCandidateList function on the "updatingCell" Cell Pointer with the updatingValue Integer
		updatingCell = m_gridBlocks[block].GetCellPointer(updatingCellLocation);						//Calls the GetCellPointer function on the Cell at position block in the CellGroup m_gridBlocks with the updatingCellLocation integer and points the "updatingCell" Cell Pointer to the result
		updatingCell->RemoveFromCandidateList(updatingValue);											//Calls the RemoveFromCandidateList function on the "updatingCell" Cell Pointer with the updatingValue Integer
	}
}

void SudokuPuzzle::IncrementSolvedCells()
{
	++solvedCells;																						//Increments the amount of total solved cells variable
}
void SudokuPuzzle::IncrementSolvedNakedSingleCells()
{
	++solvedNakedSingleCells;																			//Increments the amount of solved cells using Naked Single
}
void SudokuPuzzle::IncrementSolvedHiddenSingleCells()
{
	++solvedHiddenSingleCells;																			//Increments the amount of solved cells using Hidden Single
}
void SudokuPuzzle::IncrementPasses()
{
	++passes;																							//Increments the passes variable
}
void SudokuPuzzle::IncrementConsidered()
{
	++considered;																						//Increments the total amount of considered values
}

void SudokuPuzzle::Solve(char filenameIn[])
{
	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	InitialiseGrid(filenameIn);																					//Calls the InitialiseGrid function
	CandidateListInitialiser();																			//Calls the CandidateListInitialiser function
	SolveLoop();																						//Calls the SolveLoop function

	QueryPerformanceCounter(&end);
	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));

	Output();																							//Calls the Output function
	cout << "Time: " << time << endl;																	//Outputs the time Variable to the console
	cout << "Cells Solved Total: " << solvedCells << endl;												//Outputs the time Variable to the console
	cout << "Cells Solved Single Naked: " << solvedNakedSingleCells << endl;							//Outputs the solvedNakedSingleCells Variable to the console
	cout << "Cells Solved Single Hidden: " << solvedHiddenSingleCells << endl;							//Outputs the solvedHiddenSingleCells Variable to the console
	cout << "Passes: " << passes << endl;																//Outputs the passes Variable to the console
	cout << "Total amount of considered values: " << considered << endl;								//Outputs the considered Variable to the console
}

void SudokuPuzzle::Output() const
{
	ofstream fout("sudoku_solution.txt");																//Opens an output stream to the output file

	if (fout.is_open())																					//checks if the input stream is open
	{
		for (int cellGroup = 0; cellGroup < 9; ++cellGroup)												//Loops through every row
		{
			for (int cellLocation = 0; cellLocation < 9; ++cellLocation)								//Loops through every column
			{
				Cell *cell = m_gridRows[cellGroup].GetCellPointer(cellLocation);						//Calls the GetCellPointer function on the Cell at position cellGroup in the CellGroup m_gridRows with the cellLocation integer and points the "cell" Cell Pointer to the result
				int value = cell->GetValue();															//Calls the GetValue Cell function on the "cell" Cell Pointer and sets the value integer equal to the result
				cout << value << " ";																	//Outputs the value Variable to the console
				fout << value << " ";																	//Outputs the value Variable to the output stream
			}
			cout << endl;																				//Adds an endline to the console
			fout << endl;																				//Adds an endline to the stream
		}
		fout.close();																					//Closes the output stream
		cout << endl << endl;																			//Adds two endlines to the console
	}
}
