#pragma once
#include "pch.h"
#include "UgolkiBoard.h"

class UgolkiPlayer
{
protected:
	UgolkiBoard* board;
	CellType cellType;
	CString name;
public:
	UgolkiPlayer();
	virtual ~UgolkiPlayer();
	void SetupPlayer(CString name, CellType cellType);
	void SetBoard(UgolkiBoard* board);
	virtual bool MakeMove(unsigned int x, unsigned int y, unsigned int xx, unsigned int yy) = 0;
	CString GetName();
	virtual bool IsHuman() = 0;
};

