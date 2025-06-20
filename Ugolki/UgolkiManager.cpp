#include "pch.h"
#include "UgolkiManager.h"
#include "UgolkiHumanPlayer.h"
#include "UgolkiComputerPlayer.h"

UgolkiManager::UgolkiManager()
{
}

UgolkiManager::~UgolkiManager()
{
	delete this->player2;
	delete this->player1;
	delete this->board;
}

bool UgolkiManager::Init()
{
	return true;
}

void UgolkiManager::ShowBoard()
{

}

void UgolkiManager::MakeMove(unsigned int col)
{
	ShowBoard();
	while (!currentPlayer->MakeMove(0, 0, 0, 0))
	{
		cout << "Недопустимый ход, попробуйте еще раз" << endl;
		ShowBoard();
	}
	if (this->board->CheckEndCondition())
	{
		if (this->board->IsVictory())
			cout << "Игрок " << currentPlayer->GetName() << " победил!" << endl;
		else
			cout << "Ничья!" << endl;
		this->bGameFinished = true;
		ShowBoard();
		return;
	}
	currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool UgolkiManager::IsGameFinished()
{
	return bGameFinished;
}