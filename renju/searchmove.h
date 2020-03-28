#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//搜索核心
#include "evaluate.h"
#include "gameover.h"
#include "define.h"
#include "hash.h"
#include <algorithm>

#define SEARCH_DEPTH (12)

std::pair<point, int> searchMove(); //搜索核心

// current : 当前 player
std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta);

std::pair<point, int> findHashMap(int current, int depth, int alpha, int beta);

void recordHashMap(int depth, hashFlag flag, int value, point move);

point randomMove();

#endif
