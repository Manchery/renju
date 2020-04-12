#pragma once

#include "define.h"
#include <unordered_map>

typedef unsigned long long hash_t;

#define hashUnknowValue (inf+1)									//�����жϵ�ǰ�����Ƿ��ڹ�ϣ����

extern hash_t zobristValue[GRID_NUM][GRID_NUM][3];				//��ǰ����Ĺ�ϣֵ��¼
extern hash_t whiteFirstValue, MinFirstValue;					//���ڰ���ͺ��ֵĹ�ϣֵ
extern hash_t zobrist;											//��ǰ����hashֵ������˭���֣�������min����max

//�����������
hash_t rand64();

//��ϣ�ĳ�ʼ��
void initHashValue();

//��ϣҪ�õ��ľ�����Ϣ
enum colorFirst { blackFirst, whiteFirst };
enum whoFirst { MinFirst, MaxFirst };
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

#define HASH_CLEAN_TIME 2										//��ϣֵ���ڵ�ʱ��

extern std::unordered_map<hash_t, hashNode> hashMap;			//��ϣ��

//������ڵĹ�ϣֵ
void hashMapClean();