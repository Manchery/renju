#include "define.h"
#include <cstring>
using namespace std;

int chessBoard[GRID_NUM][GRID_NUM];//定义棋盘
int winner = blank;
std::vector<point> moveTrace[3];

int agent; // agent = black | white
int user; // user = black | white, 与 agent 相反

void clearAll() {
	agent = user = winner = blank;
	moveTrace[0].clear(); moveTrace[1].clear();
	memset(chessBoard, 0, sizeof(chessBoard));
}
