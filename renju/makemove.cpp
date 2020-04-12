#include "define.h"
#include "printchessboard.h"
#include "makemove.h"
#include "hash.h"

bool makeMove(int x, int y, int player)
{
	return makeMove(point(x, y), player);
}

bool makeMove(point pos, int player)
{
	if (chessBoard[pos.x][pos.y] != blank) return false;
	chessBoard[pos.x][pos.y] = player;
	moveTrace[player].push_back(pos);
	zobrist ^= zobristValue[pos.x][pos.y][player];
	zobrist ^= whiteFirst;
	zobrist ^= MinFirst;
	moveRecord.push_back(pos);
	remainBlank--;
	return true;
}

bool unMakeMove(int player)
{
	//³·ÏúÂä×Ó²Ù×÷
	point pos = moveTrace[player].back();
	zobrist ^= zobristValue[pos.x][pos.y][player];
	zobrist ^= whiteFirst;
	zobrist ^= MinFirst;
	moveTrace[player].pop_back();
	moveRecord.pop_back();
	chessBoard[pos.x][pos.y] = blank;
	remainBlank++;
	return true;
}