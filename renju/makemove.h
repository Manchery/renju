#ifndef _MAKEMOVE_
#define _MAKEMOVE_
//走法执行器

#include "define.h"
#include <algorithm>

bool makeMove(int x, int y, int player);//执行走法
bool makeMove(point pos, int player);//执行走法

bool unMakeMove();//撤销走法

#endif