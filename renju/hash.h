#pragma once

#include "define.h"
#include <unordered_map>

typedef unsigned long long hash_t;

#define hashUnknowValue (inf+1)

extern hash_t zobristValue[GRID_NUM][GRID_NUM][3];
extern hash_t whiteFirstValue, MinFirstValue;
extern hash_t zobrist; // 当前局面hash值，包括谁先手，先手是min还是max

hash_t rand64();

void initHashValue();

enum colorFirst { blackFirst, whiteFirst };
enum whoFirst { MinFirst, MaxFirst };
enum hashFlag { Exact, Lower, Upper };

struct hashNode {
	hash_t zobrist;
	int depth;
	hashFlag flag;
	int value;
	point move;
	hashNode() { }
	hashNode(hash_t zobrist, int depth, hashFlag flag, int value, point move, int timeStamp = 0) :
		zobrist(zobrist), depth(depth), flag(flag), value(value), move(move) { }
};

extern std::unordered_map<hash_t, hashNode> hashMap;
extern int hashSuccess;