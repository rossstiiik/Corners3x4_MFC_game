#pragma once
#include "pch.h"
#include "UgolkiBoard.h"
#include "UgolkiPlayer.h"

class UgolkiRandomPlayer : public UgolkiPlayer
{
public:
	UgolkiRandomPlayer();
	virtual ~UgolkiRandomPlayer();
	virtual bool MakeMove(unsigned int xx, unsigned int yy, unsigned int xx2, unsigned int yy2);
	virtual bool IsHuman();
};