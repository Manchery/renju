#include "define.h"
#include <cstring>
using namespace std;

bool operator ==(const point &A, const point &B) {
	return A.x == B.x && A.y == B.y;
}

int chessBoard[GRID_NUM][GRID_NUM];//��������
int winner = blank;
int remainBlank = 225; // ʣ����ÿ�λ
std::vector<point> moveTrace[3];
std::vector<point> moveRecord; // ���׼�¼
std::vector<point> currentBest; // ��������ʱ�ĵ�ǰ���Ž�


int agent; // agent = black | white
int user; // user = black | white, �� agent �෴

int getRecord; // �Ƿ�������

int timeStamp;

void clearAll() { // TODO: clear more data�������ƺ�һ�����м䲻��Ҫ clearAll
	agent = user = winner = blank;
	moveTrace[0].clear(); moveTrace[1].clear();
	memset(chessBoard, 0, sizeof(chessBoard));
}
