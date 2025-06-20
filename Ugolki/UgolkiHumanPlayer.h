#pragma once
#include "pch.h"
#include "UgolkiBoard.h"
#include "UgolkiPlayer.h"

class UgolkiHumanPlayer : public UgolkiPlayer
{
public:
	UgolkiHumanPlayer();
	virtual ~UgolkiHumanPlayer();
	virtual bool MakeMove(unsigned int xx, unsigned int yy, unsigned int xx2, unsigned int yy2);
	virtual bool IsHuman();
};