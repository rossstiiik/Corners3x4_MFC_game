#include "pch.h"
#include "UgolkiComputerPlayer.h"
#include "UgolkiBoardMonteCarloEvaluator.h"

UgolkiComputerPlayer::UgolkiComputerPlayer()
{
}

UgolkiComputerPlayer::~UgolkiComputerPlayer()
{
}
//логика движения компьютера, основанная на методе монте-карло

bool UgolkiComputerPlayer::MakeMove(unsigned int x, unsigned int y, unsigned int xx, unsigned int yy)
{
	vector <UgolkiBoardMonteCarloEvaluator*> evaluators;
	for (unsigned int i = 0; i < 8; i++)
		for (unsigned int j = 0; j < 8; j++)
			for (unsigned int v = 1; v < 5; v++)
				if (this->board->CheckLegal(i, j, v, this->cellType))
				{
					this->board->SetCell(i, j, v);
					evaluators.push_back(new UgolkiBoardMonteCarloEvaluator(this->board, 5, (this->cellType == CellType_X) ? CellType_O : CellType_X, i, j, v));
					this->board->ResetCell(i, j);
				}

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		(*evaluator)->Evaluate();

	int biggestVictories = -1;

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		if (this->cellType == CellType_X)
		{
			if ((*evaluator)->GetVictories() > biggestVictories)
				biggestVictories = (*evaluator)->GetVictories();
		}
		else
		{
			if ((*evaluator)->GetLosses() > biggestVictories)
				biggestVictories = (*evaluator)->GetLosses();
		}

	vector<UgolkiBoardMonteCarloEvaluator*> biggestWinEvaluators;
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
	{
		int numVictories;
		if (this->cellType == CellType_X)
			numVictories = (*evaluator)->GetVictories();
		else
			numVictories = (*evaluator)->GetLosses();
		if (numVictories == biggestVictories)
			biggestWinEvaluators.push_back((*evaluator));
	}

	this->board->SetCell(biggestWinEvaluators[0]->GetXPos(), biggestWinEvaluators[0]->GetYPos(), biggestWinEvaluators[0]->GetV());
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		delete (*evaluator);
	evaluators.clear();
	biggestWinEvaluators.clear();
	return true;
}

bool UgolkiComputerPlayer::IsHuman()
{
	return false;
}