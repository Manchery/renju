#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//ËÑË÷ºËÐÄ
#include "evaluate.h"
#include "gameover.h"
#include "define.h"
#include <algorithm>

point searchMove(); //ËÑË÷ºËÐÄ

std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta);

point randomMove();

#endif
