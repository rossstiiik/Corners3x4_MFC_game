#include "pch.h"
#include "UgolkiHumanPlayer.h"

UgolkiHumanPlayer::UgolkiHumanPlayer()
{
}

UgolkiHumanPlayer::~UgolkiHumanPlayer()
{
}

//перемещения человека на игроке
bool UgolkiHumanPlayer::MakeMove(unsigned int xx, unsigned int yy, unsigned int xx2, unsigned int yy2)
{
	unsigned int x, y, v;

	x = xx;
	y = yy;

	if (yy2 < y)
		v = 1;

	else if (xx2 < x)
		v = 2;

	else if (xx2 > x)
		v = 3;

	else if (yy2 > y)
		v = 4;
	else
		v = 0;

	if (this->board->CheckLegal(x, y, v, this->cellType))
	{
		this->board->SetCell(x, y, v);
		return true;
	}

	return false;
}

bool UgolkiHumanPlayer::IsHuman()
{
	return true;
}