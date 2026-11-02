#pragma once
struct Cell
{
	char displayedChar;
	bool isMined;
	bool isReavealed;
	bool isMarked;
	int mineAdjCount;
};

const char* const GREEN = "\033[32m";
const char* const YELLOW = "\033[33m";
const char* const RED = "\033[31m";
const char* const BLUE = "\033[34m";
const char* const PURPLE = "\033[35m";
const char* const RESET = "\033[0m";

Cell CreateCell();

void DisplayCell(const Cell* cell);

void MineCell(Cell* cell);

void ReavealCell(Cell* cell);

void MarkCell(Cell* cell);

bool IsCellMined(Cell* cell);

char NbrToChar(int i);
