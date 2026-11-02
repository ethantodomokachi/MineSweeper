#pragma once

#include "Cell.h"
struct Grid
{
	Cell** cellArray;
	int rowNbr;
	int colNbr;
	int totalMines;
};

Grid* CreateGrid(int rowNbr, int colNbr, int totalMines);

void InitializeGrid(Grid* grid, int rowNbr, int colNbr, int totalMines);

Cell** CreateCellArray(Grid* grid);

void DisplayGrid(const Grid* grid);

int ReturnRowNbr(int difficulty);

int ReturnColNbr(int difficulty);

int AskInt(const char* msg, int min, int max);

int GetTotalMines(int rowNbr, int colNbr);

void placeMines(Grid* grid);

int GenerateRandomNbr(int min, int max);

void CountAdjMine(Grid* grid);

void CountAdjMine(Grid* grid, int row, int col, Cell* currentCell);

Cell* GetCell(Grid* grid, int row, int col);

Cell* SelectCell(Grid* grid, bool isRevealing, int* revealedCount);

void FreeMemory(Grid* grid);