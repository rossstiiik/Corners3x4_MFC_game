#pragma once
#include "pch.h"
#include "CellType.h"


class UgolkiBoard
{
private:
	unsigned int xxpos, yypos, numMove = 0;
	int numX = 0, numO = 0, numXX = 0, numOO = 0;
	CellType cctt;
	CellType** cells;
	bool bVictory = false;
	bool IsXMade();
	bool IsOMade();
	bool IsBlockMade();
	bool IsEndMade();
public:
	UgolkiBoard();
	UgolkiBoard(UgolkiBoard* board);
	virtual ~UgolkiBoard();
	void SetCell(unsigned int xpos, unsigned int ypos, unsigned int vector);
	void ResetCell(unsigned int xpos, unsigned int ypos);
	bool CheckLegal(unsigned int xpos, unsigned int ypos, unsigned int vector, CellType ct);
	bool CheckEndCondition();
	bool IsVictory();
	unsigned int GetNumMove();
	CellType GetCell(unsigned int xpos, unsigned int ypos);
	void ClearBoard();
};