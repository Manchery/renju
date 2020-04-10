#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//��������
#include "evaluate.h"
#include "gameover.h"
#include "define.h"
#include "hash.h"
#include <algorithm>

#define SEARCH_DEPTH (12)
#define TIME_ALLOWED (50000U)

std::pair<point, int> searchMove(); //��������

// current : ��ǰ player
std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta);

std::pair<point, int> findHashMap(int current, int depth, int alpha, int beta);

void recordHashMap(int depth, hashFlag flag, int value, point move);

std::pair<point, int> idSearch(unsigned timeout = TIME_ALLOWED, int depth = SEARCH_DEPTH);

point randomMove();

#endif
