#pragma once
#include "pch.h"
#include "UgolkiBoard.h"
#include "UgolkiPlayer.h"

class UgolkiManager
{
private:
	UgolkiBoard* board;
	UgolkiPlayer* player1;
	UgolkiPlayer* player2;
	UgolkiPlayer* currentPlayer;
	bool bGameFinished = false;
public:
	UgolkiManager();
	virtual ~UgolkiManager();
	bool Init();
	void ShowBoard();
	void MakeMove(unsigned int col);
	bool IsGameFinished();
};