#ifndef _CREATEMOVES_
#define _CREATEMOVES_
//走法生成器

#include "define.h"
#include "hash.h"
#include <vector>
#include <unordered_map>
#include <vector>

#define MOVE_NUM (9U)											//搜索树的最大分支数
#define DEFEND_NUM (3U)											//保证用于防守策略的分支数

//搜索队列
extern std::unordered_map<hash_t, std::vector<point>> createdMoves;

//生成最佳的搜索队列
std::vector<point> createMoves(int player);

#endif
