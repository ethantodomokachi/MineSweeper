#include "Grid.h"
#include "Cell.h"
#include <iostream>
#include <cstdlib>

int ChooseDifficulty() {
	bool isValid = false;
	int choice;
	choice = AskInt("Choisissez la difficulte (1 : facile, 2 : moyen, 3 : difficile, 4 : personnalise ) : ",1, 4);

	return choice;
}

bool IsReavealing() {
	int userInput = AskInt("Voulez-vous marquer (0) ou reveler (1) une case", 0, 1);
	if (userInput == 0)
		return false;
	else
		return true;
}

bool CheckLoss(Cell* cell) {
	if (cell->isMined  && !cell->isMarked) {
		return true;
	}
	return false;
}

bool AskToPlayAgain() {
	int userEntry = AskInt("Voulez-vous rejouer ? (1/0)", 0, 1);
	if (userEntry == 1)
		return true;
	else
		return false;
}

void ShowPresentationMsg() {
	std::cout << "Bienvenue sur le demineur !" << std::endl
			  <<"Ici vous devrez reveler toutes les cases sans toucher aucune mines." <<std::endl 
			  <<"Une fois revelee, une case vous donne le nombre de mines adjacentes a elle" << std::endl
			  <<"Vous pouvez aussi placer un drapeau (F) sur une case pour eviter de la reveler sans faire expres" << std::endl << std::endl;
}

void PlayGame() {
	ShowPresentationMsg();
	bool isPlaying = true;
	while (isPlaying) {
		int difficulty = ChooseDifficulty();
		int rowNbr = ReturnRowNbr(difficulty);
		int colNbr = ReturnColNbr(difficulty);
		int totalMines = GetTotalMines(rowNbr, colNbr);
		int cellToWin = colNbr * rowNbr - totalMines;
		int revealedCount = 0;
		Grid* grid = CreateGrid(rowNbr, colNbr, totalMines);

		DisplayGrid(grid);
		SelectCell(grid, IsReavealing(), &revealedCount);
		placeMines(grid);
		CountAdjMine(grid);

		bool hasLost = false;
		while (revealedCount < cellToWin && !hasLost) {
			DisplayGrid(grid);
			Cell* currentCell = SelectCell(grid, IsReavealing(), &revealedCount);
			system("cls");
			if (currentCell == nullptr)
				std::cout << RED << "La case que vous avez selectionnee est soit marquee soit deja revelee, veuillez reessayer..." << RESET << std::endl << std::endl;
			else
				hasLost = CheckLoss(currentCell);
			
		}

		DisplayGrid(grid);
		if (hasLost) {
			std::cout << RED << "Argh ! vous etes tombe sur une mine... Dommage." << RESET << std::endl;
		}
		else {
			std::cout << GREEN << "Bravo ! Vous avez gagne !!!" << RESET << std::endl;
		}
		FreeMemory(grid);
		if (grid == nullptr) {
			std::cout << "djhakhdka" << std::endl;
		}
		isPlaying = AskToPlayAgain();
	}
}

int main() {
	srand(time(NULL));
	PlayGame();
	
	return 0;
}