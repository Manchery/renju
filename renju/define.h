
#ifndef _DEFINE_
#define _DEFINE_
//全局变量定义

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

#define blank (0)		//空白点
#define black (1)		//黑方
#define white (2)		//白方
#define opposite(x) (3-(x)) // 对方
#define inf (1<<30)
#define winValue (100000000)
#define inboard(a,b) ((a)>0 && (a)<=15 && (b)>0 && (b)<=15)		//用于检验招法是否在棋盘上

#define GRID_NUM 16	//棋盘规模	
extern int chessBoard[GRID_NUM][GRID_NUM]; //棋盘
extern int winner;
extern std::vector<point> moveTrace[3];

extern int agent; // agent = black | white
extern int user; // user = black | white, 与 agent 相反

extern int timeStamp;

void clearAll();

#endif


