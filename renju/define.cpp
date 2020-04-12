#include "define.h"
#include <cstring>
using namespace std;

//点对运算符的重载
bool operator ==(const point &A, const point &B) {
	return A.x == B.x && A.y == B.y;
}

int chessBoard[GRID_NUM][GRID_NUM];						//棋盘
int winner = blank;										//记录游戏结束时的赢家或平局状态
int remainBlank = 225;									//棋盘中的剩余可用空位
std::vector<point> moveRecord;							//下棋记录
int agent;												//AI扮演的角色(黑棋/白棋)
int user;												//玩家扮演的角色(与AI相反)
int getRecord;											//是否检测到记录的棋谱
int timeStamp;											//时间戳

//清空记录
void clearAll() {
	agent = user = winner = blank;
	memset(chessBoard, 0, sizeof(chessBoard));
}
