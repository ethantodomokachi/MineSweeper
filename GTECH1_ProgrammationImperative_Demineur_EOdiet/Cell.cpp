#include "Cell.h"
#include <iostream>
#include <cstdlib>

Cell CreateCell() {
	Cell cell = { ' ', false, false, false, 0 };
	return cell;
}

void DisplayCell(const Cell* cell) {
	switch (cell->displayedChar) {
	case '0':
		std::cout << GREEN;
		break;
	case '1':
		std::cout << YELLOW;
		break;
	case '2':
		std::cout << RED;
		break;
	case '3':
		std::cout << BLUE;
		break;
	default:
		std::cout << PURPLE;
		break;
	}
	std::cout << cell->displayedChar;
	std::cout << RESET;
}

void MineCell(Cell* cell) {
	cell->isMined = true;
}

void ReavealCell(Cell* cell) {
	if (cell->isMined) {
		cell->displayedChar = '*';
	}
	else {
		cell->displayedChar = NbrToChar(cell->mineAdjCount);
	}
}

void MarkCell(Cell* cell) {
	cell->displayedChar = 'F';
}

bool IsCellMined(Cell* cell) {
	return cell->isMined;
}

char NbrToChar(int i) {
	return (char)i + 48;
}