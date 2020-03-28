#ifndef _CREATEMOVES_
#define _CREATEMOVES_
//走法生成器

#include "define.h"
#include "hash.h"
#include <vector>
#include <unordered_map>
#include <vector>

// 这里要保持它是偶数，详见对它的引用(createsMove)
// 或者修改时记得将createsMove里的相应部分修改合理
#define MOVE_NUM (8U) 

extern std::unordered_map<hash_t, std::vector<point>> createdMoves;

std::vector<point> createMoves(int player, int depth = 0);

#endif
