#ifndef _MAKEMOVE_
#define _MAKEMOVE_
//走法执行器

#include "define.h"
#include <algorithm>

//执行走法
bool makeMove(int x, int y, int player);
bool makeMove(point pos, int player);

//撤销走法
bool unMakeMove(int player);

#endif