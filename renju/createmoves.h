#ifndef _CREATEMOVES_
#define _CREATEMOVES_
//�߷�������

#include "define.h"
#include "hash.h"
#include <vector>
#include <unordered_map>
#include <vector>

// ����Ҫ��������ż�����������������(createsMove)
// �����޸�ʱ�ǵý�createsMove�����Ӧ�����޸ĺ���
#define MOVE_NUM (8U) 

extern std::unordered_map<hash_t, std::vector<point>> createdMoves;

std::vector<point> createMoves(int player, int depth = 0);

#endif
