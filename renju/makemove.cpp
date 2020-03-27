#include "define.h"
#include "printchessboard.h"
#include "makemove.h"

bool makeMove(int x, int y, int player)
{
	return makeMove(point(x, y), player);
}

bool makeMove(point pos, int player)
{
	chessBoard[pos.x][pos.y] = player;
	moveTrace[player].push_back(pos);
	return true;
}

bool unMakeMove()
{
	//³·ÏúÂä×Ó²Ù×÷£¨chessboard[i][j]=0£©
	return true;
}
