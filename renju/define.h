
#ifndef _DEFINE_
#define _DEFINE_
//ȫ�ֱ�������

#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

struct point {
	int x, y;
	point(int x=0, int y=0):x(x),y(y) {} 
};
bool operator ==(const point &A, const point &B);

#define blank (0)		//�հ׵�
#define black (1)		//�ڷ�
#define white (2)		//�׷�
#define opposite(x) (3-(x)) // �Է�
#define inf (1<<30)
#define winValue (100000000)
#define inboard(a,b) ((a)>0 && (a)<=15 && (b)>0 && (b)<=15)		//���ڼ����з��Ƿ���������

#define GRID_NUM 16	//���̹�ģ	
extern int chessBoard[GRID_NUM][GRID_NUM]; //����
extern int winner;
extern std::vector<point> moveTrace[3];

extern int agent; // agent = black | white
extern int user; // user = black | white, �� agent �෴

extern int timeStamp;

void clearAll();

#endif


