#include "SudokuPuzzle.h"

// This is a basic starting point for you to use to implement your Sudoku solver
int main(int argc, char **) {
	SudokuPuzzle puzzle;												//Creates a new instance of the SudokuPuzzle class called puzzle
	puzzle.Solve("sudoku_puzzle.txt");									//Calls the solve function on the puzzle instance

	system("pause");

	return 0;
}
