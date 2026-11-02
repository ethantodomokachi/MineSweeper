#include "Grid.h"
#include <iostream>
#include <cstdlib>

Grid* CreateGrid(int rowNbr, int colNbr, int totalMines) {
	Grid* p = (Grid*)malloc(sizeof(Grid));
	if (p == nullptr) {
		exit(1);
	}
	InitializeGrid(p, rowNbr, colNbr, totalMines);

	return p;
}

void InitializeGrid(Grid* grid, int rowNbr, int colNbr, int totalMines) {
	grid->rowNbr = rowNbr;
	grid->colNbr = colNbr;
	grid->cellArray = CreateCellArray(grid);
	grid->totalMines = totalMines;
}

Cell** CreateCellArray(Grid* grid) {
	Cell** p = (Cell**)malloc(sizeof(Cell*) * grid->rowNbr);
	if (p == nullptr) {
		exit(1);
	}

	for (int row = 0; row < grid->rowNbr; row++) {
		p[row] = (Cell*)malloc(sizeof(Cell) * grid->colNbr);
		if (p[row] == nullptr) {
			exit(1);
		}
		for (int col = 0; col < grid->colNbr; col++) {
			p[row][col] = CreateCell();
		}
	}
	return p;
}

void DisplayGrid(const Grid* grid) {
	std::cout << ' ';
	for(int i = 0; i < grid->colNbr; i++) {
		if(i < 10)
			std::cout << "  " << i;
		else
			std::cout << " " << i;
	}
	std::cout << std::endl;
	for (int row = 0; row < grid->rowNbr; row++) {
		std::cout << row;
		if (row < 10)
			std::cout << " ";

		for (int col = 0; col < grid->colNbr; col++) {
			std::cout << '[';
			if (grid->cellArray[row][col].isMarked) {
				MarkCell(&grid->cellArray[row][col]);
			}
			else if (grid->cellArray[row][col].isReavealed) {
				ReavealCell(&grid->cellArray[row][col]);
			}
			DisplayCell(&grid->cellArray[row][col]);
			std::cout << ']';
		}
		std::cout << std::endl;
	}
}

int ReturnRowNbr(int difficulty) {
	switch (difficulty) {
	case 1: return 9;
	case 2: return 16;
	case 3: return 16;
	case 4: {
		return AskInt("Entrez le nombre de lignes : ", 2, 50);
	}
	}
}

int ReturnColNbr(int difficulty) {
	switch (difficulty) {
	case 1: return 9;
	case 2: return 16;
	case 3: return 30;
	case 4: {
		return AskInt("Entrez le nombre de colonnes : ", 2, 35);
	}
	}
}

int AskInt(const char* msg, int min, int max) {
	int userInput;
	bool isValid = false;

	while(!isValid) {
		std::cout << msg << std::endl;
		std::cin >> userInput;

		if (userInput < min || userInput > max) {
			std::cout << "Saisie invalide, reessayez " << std::endl;
		}
		else {
			isValid = true;
		}
	}
	return userInput;
}

int GetTotalMines(int rowNbr, int colNbr) {
	return (rowNbr * colNbr * 15) / 100;
}

void placeMines(Grid* grid) {
	int totalMines = grid->totalMines;
	for (int i = 0; i < totalMines; i++) {
		bool isValid = false;
		while (!isValid) {
			int randRow = GenerateRandomNbr(0, grid->rowNbr-1);
			int randCol = GenerateRandomNbr(0, grid->colNbr - 1);

			if (grid->cellArray[randRow][randCol].isMined == false && grid->cellArray[randRow][randCol].isReavealed == false) {
				MineCell(&grid->cellArray[randRow][randCol]);
				isValid = true;
			}
		}
	}
}

int GenerateRandomNbr(int min, int max) {
	int randomNumber = 0;
	randomNumber = rand() % (max + 1 - min);
	randomNumber += min;
	return randomNumber;
}

void CountAdjMine(Grid* grid) {
	for (int row = 0; row < grid->rowNbr; row++) {
		for (int col = 0; col < grid->colNbr; col++) {
			Cell* currentCell = &grid->cellArray[row][col];
			if (!IsCellMined(currentCell)) {
				CountAdjMine(grid, row, col, currentCell);
			}
		}
	}
}

void CountAdjMine(Grid* grid, int row, int col, Cell* currentCell) {
	int mineCount = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			Cell* cell = GetCell(grid, row + i, col + j);

			if (cell == nullptr) {
				continue;
			}
			if (cell->isMined) {
				mineCount++;
			}
			
		}
	}
	currentCell->mineAdjCount = mineCount;
}

Cell* GetCell(Grid* grid, int row, int col) {
	if (row < 0 || row >= grid->rowNbr) {
		return nullptr;
	}

	if (col < 0 || col >= grid->colNbr) {
		return nullptr;
	}

	return &grid->cellArray[row][col];
}

Cell* SelectCell(Grid* grid, bool isRevealing, int* revealedCount) {
	int SelectedRow = AskInt("Selectionnez la ligne de votre case : ", 0, grid->rowNbr);
	int SelectedCol = AskInt("Selectionnez la collonne de votre case : ", 0, grid->colNbr);

	Cell* cell = GetCell(grid, SelectedRow, SelectedCol);
	
	if (cell->isReavealed) {
		return nullptr;
	}
	if(isRevealing) {
		if (cell->isMarked) {
			return nullptr;
		}
		cell->isReavealed = true;
		*revealedCount = *revealedCount + 1;
	}
	else {
		if (cell->isMarked) {
			cell->isMarked = false;
		}
		cell->isMarked = true;
	}

	return cell;
}

void FreeMemory(Grid* grid) {
	for (int row = 0; row < grid->rowNbr; row++) {
		free(grid->cellArray[row]);
	}
	free(grid->cellArray);
	free(grid);
}
