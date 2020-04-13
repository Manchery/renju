#include "define.h"
#include <cstring>
using namespace std;

bool operator ==(const point &A, const point &B) {
	return A.x == B.x && A.y == B.y;
}

int chessBoard[GRID_NUM][GRID_NUM];						//����
int winner = blank;										//��¼��Ϸ����ʱ��Ӯ�һ�ƽ��״̬
int remainBlank = 225;									//�����е�ʣ����ÿ�λ
std::vector<point> moveRecord;							//�����¼
int agent;												//AI���ݵĽ�ɫ(����/����)
int user;												//��Ұ��ݵĽ�ɫ(��AI�෴)
int timeStamp;											//ʱ���