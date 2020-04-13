#pragma once

#include "define.h"
#include <unordered_map>

typedef unsigned long long hash_t;

#define hashUnknowValue (inf+1)									//���ڱ�ʾ��ǰ�����Ƿ��ڹ�ϣ����

extern hash_t zobristValue[GRID_NUM][GRID_NUM][3];				//ÿ��λ�õ�ÿ�����ӵ�zobristֵ
extern hash_t whiteFirstValue, MinFirstValue;					//��ǰ�������к�������е�zobristֵ
extern hash_t zobrist;											//��ǰ����zobristֵ������˭���֣�������min����max

//�����������
hash_t rand64();

//zobristֵ�ĳ�ʼ��
void initHashValue();

//hash�ڵ��еĹ�ֵ��ǩ������
enum hashFlag { Exact, Lower, Upper };

//��ϣ�ڵ�
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
extern std::unordered_map<hash_t, hashNode> hashMap;			//��ϣ��

#define HASH_CLEAN_TIME 2										//��ϣ�ڵ���ڵ�ʱ��
//������δ�����ʵĹ�ϣ�ڵ�
void hashMapClean();