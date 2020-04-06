#ifndef _CREATEMOVES_
#define _CREATEMOVES_
//走法生成器

#include "define.h"
#include "hash.h"
#include <vector>
#include <unordered_map>
#include <vector>

#define MOVE_NUM (8U)
#define DEFEND_NUM (3U) // DEFEND_NUM = (MOVE_NUM / 2) - 1;

extern std::unordered_map<hash_t, std::vector<point>> createdMoves;

std::vector<point> createMoves(int player, int depth = 0);

#endif
