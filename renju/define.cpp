#include "define.h"
#include <cstring>
using namespace std;

int chessBoard[GRID_NUM][GRID_NUM];//��������
int winner = blank;
std::vector<point> moveTrace[3];

int agent; // agent = black | white
int user; // user = black | white, �� agent �෴

void clearAll() {
	agent = user = winner = blank;
	moveTrace[0].clear(); moveTrace[1].clear();
	memset(chessBoard, 0, sizeof(chessBoard));
}
