#ifndef _CREATEMOVES_
#define _CREATEMOVES_
//�߷�������

#include "define.h"
#include "hash.h"
#include <vector>
#include <unordered_map>
#include <vector>

#define MOVE_NUM (9U)											//������������֧��
#define DEFEND_NUM (3U)											//��֤���ڷ��ز��Եķ�֧��

//�Ѿ�ִ�й�createMoves�ľ��棬��¼����������ظ�
extern std::unordered_map<hash_t, std::vector<point>> createdMoves;

//������ѵ���չ������������
std::vector<point> createMoves(int player);

#endif
