#pragma once
#include "CellGroup.h"
#include <iostream>
#include <fstream>
using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void) : solvedCells(NULL), oldSolvedCells(NULL), solvedNakedSingleCells(NULL), solvedHiddenSingleCells(NULL), passes(NULL), calculated(NULL), considered(NULL), solved(NULL) {}
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);

private:
	CellGroup m_gridRows[9];												//Reserves space in memory for a member CellGroup variable with 9 members
	CellGroup m_gridColumns[9];												//Reserves space in memory for a member CellGroup variable with 9 members
	CellGroup m_gridBlocks[9];												//Reserves space in memory for a member CellGroup variable with 9 members

	void InitialiseGrid(char filenameIn[]);

	void CandidateListInitialiser() const;

	void CandidateListRowUpdater(int cellGroup, int cellLocation, int activeValue, int comparableCell) const;
	void CandidateListColumnUpdater(int cellGroup, int cellLocation, int activeValue, int comparableCell) const;
	void CandidateListBlockUpdater(int cellGroup, int cellLocation, int activeValue, int comparableCell) const;

	void CandidateListUpdater(Cell *cell) const;

	bool NakedSingle(Cell *cell);
	bool HiddenSingle(Cell *cell);

	void SolveLoop();

	void HiddenComparableCandidateListLoop(Cell *comparableCell, int value, std::vector<int> &tempCandidateList) const;
	bool HiddenCandidateListChecker(Cell *cell, std::vector<int> &tempCandidateList);
	bool HiddenRowLoop(Cell *cell);
	bool HiddenColumnLoop(Cell *cell);
	bool HiddenBlockLoop(Cell *cell);

	void IncrementSolvedCells();
	void IncrementSolvedNakedSingleCells();
	void IncrementSolvedHiddenSingleCells();
	void IncrementPasses();
	void IncrementConsidered();

	int solvedCells = 0;													//Initialise an integer member variable and set its value to 0
	int oldSolvedCells = 0;													//Initialise an integer member variable and set its value to 0
	int solvedNakedSingleCells = 0;											//Initialise an integer member variable and set its value to 0
	int solvedHiddenSingleCells = 0;										//Initialise an integer member variable and set its value to 0
	int passes = 0;															//Initialise an integer member variable and set its value to 0
	int calculated = 0;														//Initialise an integer member variable and set its value to 0
	int considered = 0;														//Initialise an integer member variable and set its value to 0
	bool solved = false;													//Initialise an bool member variable and set its value to false

	void Output() const;
};

