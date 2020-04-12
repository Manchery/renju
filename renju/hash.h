#pragma once

#include "define.h"
#include <unordered_map>

typedef unsigned long long hash_t;

#define hashUnknowValue (inf+1)									//用于判断当前局面是否在哈希表中

extern hash_t zobristValue[GRID_NUM][GRID_NUM][3];				//当前局面的哈希值记录
extern hash_t whiteFirstValue, MinFirstValue;					//用于白棋和后手的哈希值
extern hash_t zobrist;											//当前局面hash值，包括谁先手，先手是min还是max

//随机数生成器
hash_t rand64();

//哈希的初始化
void initHashValue();

//哈希要用到的局面信息
enum colorFirst { blackFirst, whiteFirst };
enum whoFirst { MinFirst, MaxFirst };
enum hashFlag { Exact, Lower, Upper };

//哈希节点
struct hashNode {
	hash_t zobrist;
	int depth;
	hashFlag flag;
	int value;
	point move;
	int time;
	hashNode() { }
	hashNode(hash_t zobrist, int depth, hashFlag flag, int value, point move, int time) :
		zobrist(zobrist), depth(depth), flag(flag), value(value), move(move), time(time) { }
};

#define HASH_CLEAN_TIME 2										//哈希值过期的时间

extern std::unordered_map<hash_t, hashNode> hashMap;			//哈希表

//清理过期的哈希值
void hashMapClean();