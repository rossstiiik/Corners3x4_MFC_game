#pragma once
#include "pch.h"
#include "UgolkiBoard.h"
#include "UgolkiPlayer.h"

class UgolkiComputerPlayer : public UgolkiPlayer
{
public:
	UgolkiComputerPlayer();
	virtual ~UgolkiComputerPlayer();
	virtual bool MakeMove(unsigned int x, unsigned int y, unsigned int xx, unsigned int yy);
	virtual bool IsHuman();
};

