#pragma once
#include "pch.h"
#include "UgolkiBoard.h"

class UgolkiBoardMonteCarloEvaluator
{
private:
	UgolkiBoard* board;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;
	unsigned int xpos, ypos, v;
	CellType startCellType;
public:
	UgolkiBoardMonteCarloEvaluator(UgolkiBoard* board, int numIterations, CellType startCellType, unsigned int xpos, unsigned int ypos, unsigned int v);
	~UgolkiBoardMonteCarloEvaluator();
	void EvaluatedBoard();
	void Evaluate();
	int GetVictories() { return numVictories; }
	int GetLosses() { return numLosses; }
	int GetDraws() { return numDraws; }
	int GetXPos() { return xpos; }
	int GetYPos() { return ypos; }
	int GetV() { return v; }
};