#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_

//搜索核心

#include "evaluate.h"
#include "gameover.h"
#include "define.h"
#include "hash.h"
#include <algorithm>

#define SEARCH_DEPTH (12)										//参考的最大搜索深度
#define TIME_ALLOWED (10000U)									//迭代加深搜索的最长时间限制

//搜索的入口函数
std::pair<point, int> searchMove(); 

//带alpha-beta剪枝的Minimax搜索算法
//current : 当前 player
std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta);

//查找当前局面的哈希值
std::pair<point, int> findHashMap(int current, int depth, int alpha, int beta);

//记录哈希值
void recordHashMap(int depth, hashFlag flag, int value, point move);

//迭代加深搜索
std::pair<point, int> idSearch(unsigned timeout = TIME_ALLOWED, int depth = SEARCH_DEPTH);

//快速防守
std::pair<point, int> fastDefend();

#endif
