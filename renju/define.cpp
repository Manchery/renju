#include "define.h"
#include <cstring>
using namespace std;

bool operator ==(const point &A, const point &B) {
	return A.x == B.x && A.y == B.y;
}

int chessBoard[GRID_NUM][GRID_NUM];//定义棋盘
int winner = blank;
int remainBlank = 225; // 剩余可用空位
std::vector<point> moveTrace[3];
std::vector<point> moveRecord; // 棋谱记录
std::vector<point> currentBest; // 迭代加深时的当前最优解


int agent; // agent = black | white
int user; // user = black | white, 与 agent 相反

int getRecord; // 是否有棋谱

int timeStamp;

void clearAll() { // TODO: clear more data，不过似乎一盘棋中间不需要 clearAll
	agent = user = winner = blank;
	moveTrace[0].clear(); moveTrace[1].clear();
	memset(chessBoard, 0, sizeof(chessBoard));
}
