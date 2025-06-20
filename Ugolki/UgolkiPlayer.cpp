#include "pch.h"
#include "UgolkiPlayer.h"

UgolkiPlayer::UgolkiPlayer()
{
}

UgolkiPlayer::~UgolkiPlayer()
{
}

void UgolkiPlayer::SetupPlayer(CString name, CellType cellType)
{
	this->name = name;
	this->cellType = cellType;
}

void UgolkiPlayer::SetBoard(UgolkiBoard* board)
{
	this->board = board;
}

CString UgolkiPlayer::GetName()
{
	return this->name;
}