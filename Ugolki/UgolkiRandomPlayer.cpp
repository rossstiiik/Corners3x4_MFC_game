#include "pch.h"
#include "UgolkiRandomPlayer.h"

UgolkiRandomPlayer::UgolkiRandomPlayer()
{
}

UgolkiRandomPlayer::~UgolkiRandomPlayer()
{
}


bool UgolkiRandomPlayer::MakeMove(unsigned int xx, unsigned int yy, unsigned int xx2, unsigned int yy2)
{
	unsigned int x, y, v;
	v = (unsigned int)(rand() % 4 + 1);
	x = (unsigned int)(rand() % 8);
	y = (unsigned int)(rand() % 8);

	if (this->board->CheckLegal(x, y, v, this->cellType))
	{
		this->board->SetCell(x, y, v);
		return true;
	}

	return false;
}

bool UgolkiRandomPlayer::IsHuman()
{
	return false;
}