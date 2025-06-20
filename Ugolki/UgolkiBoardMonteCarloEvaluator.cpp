#include "pch.h"
#include "UgolkiBoardMonteCarloEvaluator.h"
#include "UgolkiRandomPlayer.h"

UgolkiBoardMonteCarloEvaluator::UgolkiBoardMonteCarloEvaluator(UgolkiBoard* board, int numIterations, CellType startCellType, unsigned int xpos, unsigned int ypos, unsigned int v)
{
	this->board = board;
	this->numGames = numIterations;
	this->numDraws = 0;
	this->numVictories = 0;
	this->numLosses = 0;
	this->xpos = xpos;
	this->ypos = ypos;
	this->v = v;
	this->startCellType = startCellType;
}

UgolkiBoardMonteCarloEvaluator::~UgolkiBoardMonteCarloEvaluator()
{

}

void UgolkiBoardMonteCarloEvaluator::EvaluatedBoard()
{
	UgolkiBoard* b = new UgolkiBoard(this->board);
	UgolkiRandomPlayer* player1 = new UgolkiRandomPlayer();
	UgolkiRandomPlayer* player2 = new UgolkiRandomPlayer();
	UgolkiRandomPlayer* currentPlayer;
	bool bGameFinished = false;

	player1->SetupPlayer(L"RandomX", CellType_X);
	player2->SetupPlayer(L"RandomO", CellType_O);
	player1->SetBoard(b);
	player2->SetBoard(b);
	currentPlayer = (this->startCellType == CellType_X) ? player2 : player1;

	if (b->CheckEndCondition())
	{
		if (b->IsVictory())
			if (currentPlayer == player1)
				numLosses++;
			else
				numVictories++;
		else
			numDraws++;
		bGameFinished = true;
		delete b;
		delete player1;
		delete player2;
		return;
	}

	while (!bGameFinished)
	{
		while (!currentPlayer->MakeMove(0, 0, 0, 0));

		if (b->CheckEndCondition())
		{
			if (b->IsVictory())
				if (currentPlayer == player1)
					numVictories++;
				else
					numLosses++;
			else
				numDraws++;
			bGameFinished = true;
		}
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	}
	delete b;
	delete player1;
	delete player2;
}

void UgolkiBoardMonteCarloEvaluator::Evaluate()
{
	for (int i = 0; i < numGames; i++)
		EvaluatedBoard();
}