#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//��������
#include "evaluate.h"
#include "gameover.h"
#include "define.h"
#include <algorithm>

point searchMove(); //��������

std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta);

point randomMove();

#endif
