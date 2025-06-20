#include "pch.h"
#include "UgolkiBoard.h"
//Создание логической состовляющей доски
UgolkiBoard::UgolkiBoard()
{
	cells = new CellType * [8];
	for (unsigned int i = 0; i < 8; i++)
		cells[i] = new CellType[8];

	for (unsigned int i = 0; i < 8; i++)
		for (unsigned int j = 0; j < 8; j++)
			cells[i][j] = CellType_Empty;

	for (unsigned int i = 5; i < 8; i++)
		for (unsigned int j = 0; j < 4; j++)
			cells[i][j] = CellType_X;

	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 4; j < 8; j++)
			cells[i][j] = CellType_O;
}

UgolkiBoard::UgolkiBoard(UgolkiBoard* board)
{
	cells = new CellType * [8];
	for (unsigned int i = 0; i < 8; i++)
		cells[i] = new CellType[8];
	for (unsigned int i = 0; i < 8; i++)
		for (unsigned int j = 0; j < 8; j++)
			cells[j][i] = board->cells[j][i];
}

UgolkiBoard::~UgolkiBoard()
{
	for (unsigned int i = 0; i < 8; i++)
		delete[]cells[i];
	delete[]cells;
	numMove = 0;
}

//логическое перемещение фигур по доске
void UgolkiBoard::SetCell(unsigned int xpos, unsigned int ypos, unsigned int vector)
{
	xxpos = xpos;
	yypos = ypos;
	switch (vector)
	{
	case 1:
		if (cells[ypos - 1][xpos] == CellType_Empty)
		{
			cctt = cells[ypos - 1][xpos];
			cells[ypos - 1][xpos] = cells[ypos][xpos];
			yypos = yypos - 1;
			numMove++;
		}
		else if (cells[ypos - 2][xpos] == CellType_Empty)
		{
			cctt = cells[ypos - 2][xpos];
			cells[ypos - 2][xpos] = cells[ypos][xpos];
			yypos = yypos - 2;
			numMove++;
		}
		cells[ypos][xpos] = CellType_Empty;
		break;
	case 2:
		if (cells[ypos][xpos - 1] == CellType_Empty)
		{
			cctt = cells[ypos][xpos - 1];
			cells[ypos][xpos - 1] = cells[ypos][xpos];
			xxpos = xxpos - 1;
			numMove++;
		}
		else if (cells[ypos][xpos - 2] == CellType_Empty)
		{
			cctt = cells[ypos][xpos - 2];
			cells[ypos][xpos - 2] = cells[ypos][xpos];
			xxpos = xxpos - 2;
			numMove++;
		}
		cells[ypos][xpos] = CellType_Empty;
		break;
	case 3:
		if (cells[ypos][xpos + 1] == CellType_Empty)
		{
			cctt = cells[ypos][xpos + 1];
			cells[ypos][xpos + 1] = cells[ypos][xpos];
			xxpos = xxpos + 1;
			numMove++;
		}
		else if (cells[ypos][xpos + 2] == CellType_Empty)
		{
			cctt = cells[ypos][xpos + 2];
			cells[ypos][xpos + 2] = cells[ypos][xpos];
			xxpos = xxpos + 2;
			numMove++;
		}
		cells[ypos][xpos] = CellType_Empty;
		break;
	case 4:
		if (cells[ypos + 1][xpos] == CellType_Empty)
		{
			cctt = cells[ypos + 1][xpos];
			cells[ypos + 1][xpos] = cells[ypos][xpos];
			yypos = yypos + 1;
			numMove++;
		}
		else if (cells[ypos + 2][xpos] == CellType_Empty)
		{
			cctt = cells[ypos + 2][xpos];
			cells[ypos + 2][xpos] = cells[ypos][xpos];
			yypos = yypos + 2;
			numMove++;
		}
		cells[ypos][xpos] = CellType_Empty;
		break;
	}
}

void UgolkiBoard::ResetCell(unsigned int xpos, unsigned int ypos)
{
	cells[ypos][xpos] = cells[yypos][xxpos];
	cells[yypos][xxpos] = cctt;
	numMove--;

}
//проверка возможности такого перемещения
bool UgolkiBoard::CheckLegal(unsigned int xpos, unsigned int ypos, unsigned int vector, CellType ct)
{
	if ((xpos < 0) || (xpos > 7) || (ypos < 0) || (ypos > 7))
		return false;
	if ((cells[ypos][xpos] == CellType_Empty) || (cells[ypos][xpos] != ct)) return false;
	switch (vector)
	{
	case 1:
		yypos = ypos - 1;
		if ((yypos < 0) || (yypos > 7))
			return false;
		if (cells[ypos - 1][xpos] == CellType_Empty)
			return true;
		else if ((cells[ypos - 1][xpos] == CellType_X) || (cells[ypos - 1][xpos] == CellType_O))
		{
			yypos = ypos - 2;
			if ((yypos < 0) || (yypos > 7))
				return false;
			if (cells[ypos - 2][xpos] == CellType_Empty)
				return true;
			else return false;
		}
		break;
	case 2:
		xxpos = xpos - 1;
		if ((xxpos < 0) || (xxpos > 7))
			return false;
		if (cells[ypos][xpos - 1] == CellType_Empty)
			return true;
		else if ((cells[ypos][xpos - 1] == CellType_X) || (cells[ypos][xpos - 1] == CellType_O))
		{
			xxpos = xpos - 2;
			if ((xxpos < 0) || (xxpos > 7))
				return false;
			if (cells[ypos][xpos - 2] == CellType_Empty)
				return true;
			else return false;
		}
		break;
	case 3:
		xxpos = xpos + 1;
		if ((xxpos < 0) || (xxpos > 7))
			return false;
		if (cells[ypos][xpos + 1] == CellType_Empty)
			return true;
		else if ((cells[ypos][xpos + 1] == CellType_X) || (cells[ypos][xpos + 1] == CellType_O))
		{
			xxpos = xpos + 2;
			if ((xxpos < 0) || (xxpos > 7))
				return false;
			if (cells[ypos][xpos + 2] == CellType_Empty)
				return true;
			else return false;
		}
		break;
	case 4:
		yypos = ypos + 1;
		if ((yypos < 0) || (yypos > 7))
			return false;
		if (cells[ypos + 1][xpos] == CellType_Empty)
			return true;
		else if ((cells[ypos + 1][xpos] == CellType_X) || (cells[ypos + 1][xpos] == CellType_O))
		{
			yypos = ypos + 2;
			if ((yypos < 0) || (yypos > 7))
				return false;
			if (cells[ypos + 2][xpos] == CellType_Empty)
				return true;
			else return false;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

//Создание стартовой расстановки
bool UgolkiBoard::IsXMade()
{
	int numX = 0;

	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 5; j < 8; j++)
			if (cells[i][j] == CellType_X)
				numX++;

	if ((numX == 9))
	{
		bVictory = true;
		return true;
	}

	return false;
}

bool UgolkiBoard::IsOMade()
{
	int numO = 0;

	for (unsigned int i = 5; i < 8; i++)
		for (unsigned int j = 0; j < 3; j++)
			if (cells[i][j] == CellType_O)
				numO++;

	if ((numO == 9))
	{
		bVictory = true;
		return true;
	}

	return false;
}

//Условие победы по максимуму шагов
bool UgolkiBoard::IsBlockMade()
{	
	if (numMove == 100)
	{
		for (unsigned int i = 5; i < 8; i++)
			for (unsigned int j = 0; j < 3; j++)
				if (cells[i][j] == CellType_X)
					numX++;
		for (unsigned int i = 0; i < 3; i++)
			for (unsigned int j = 5; j < 8; j++)
				if (cells[i][j] == CellType_O)
					numO++;
		if (numX > numO)
		{
			bVictory = true;
			return true;
		}
		else if ((numO != 0) && (numX !=0) && (numO == numX))
			return true;
	}
	if (numMove == 101)
	{
		if (numO > numX)
		{
			bVictory = true;
			return true;
		}
		else if ((numO != 0) && (numX != 0) && (numO == numX))
			return true;
	}
	return false;
}

bool UgolkiBoard::IsEndMade()
{
	if (numMove == 200)
	{
		for (unsigned int i = 5; i < 8; i++)
			for (unsigned int j = 0; j < 3; j++)
				if (cells[i][j] == CellType_O)
					numOO++;
		for (unsigned int i = 0; i < 3; i++)
			for (unsigned int j = 5; j < 8; j++)
				if (cells[i][j] == CellType_X)
					numXX++;
		if (numXX < numOO)
		{
			bVictory = true;
			return true;
		}
		else if ((numOO != 0) && (numXX != 0) && (numOO == numXX))
			return true;
	}
	if (numMove == 201)
	{
		if (numOO < numXX)
		{
			bVictory = true;
			return true;
		}
		else if ((numOO != 0) && (numXX != 0) && (numOO == numXX))
			return true;
	}
	return false;
}

bool UgolkiBoard::CheckEndCondition()
{
	if (IsXMade() || IsOMade() || IsBlockMade() || IsEndMade())
		return true;

	return false;
}

bool UgolkiBoard::IsVictory()
{
	return bVictory;
}


CellType UgolkiBoard::GetCell(unsigned int xpos, unsigned int ypos)
{
	return cells[ypos][xpos];
}
//обновление доски
void UgolkiBoard::ClearBoard()
{
	for (unsigned int i = 0; i < 8; i++)
		for (unsigned int j = 0; j < 8; j++)
			cells[i][j] = CellType_Empty;
	for (unsigned int i = 5; i < 8; i++)
		for (unsigned int j = 0; j < 3; j++)
			cells[i][j] = CellType_X;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 5; j < 8; j++)
			cells[i][j] = CellType_O;
	numMove = 0;
}

unsigned int UgolkiBoard::GetNumMove()
{
	return this->numMove;
}