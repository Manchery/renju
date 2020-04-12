#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_

//��������

#include "evaluate.h"
#include "gameover.h"
#include "define.h"
#include "hash.h"
#include <algorithm>

#define SEARCH_DEPTH (12)										//�ο�������������
#define TIME_ALLOWED (10000U)									//���������������ʱ������

//��������ں���
std::pair<point, int> searchMove(); 

//��alpha-beta��֦��Minimax�����㷨
//current : ��ǰ player
std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta);

//���ҵ�ǰ����Ĺ�ϣֵ
std::pair<point, int> findHashMap(int current, int depth, int alpha, int beta);

//��¼��ϣֵ
void recordHashMap(int depth, hashFlag flag, int value, point move);

//������������
std::pair<point, int> idSearch(unsigned timeout = TIME_ALLOWED, int depth = SEARCH_DEPTH);

//���ٷ���
std::pair<point, int> fastDefend();

#endif
