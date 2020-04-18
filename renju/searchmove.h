#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_

//��������

#include "evaluate.h"
#include "gameover.h"
#include "define.h"
#include "hash.h"
#include <algorithm>

extern int searchDepth;											// ��¼��ǰ������������
#define TIME_ALLOWED (5.0)										//���������������ʱ�����ƣ���λ����

extern clock_t start_clock;										//��ʼ������ʱ��

//��������ں���
std::pair<point, int> searchMove(); 

//��alpha-beta��֦��Minimax�����㷨
//current : ��ǰ player
std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta);

//������������
std::pair<point, int> idSearch();

//���ٷ���
std::pair<point, int> fastDefend();

//���ҵ�ǰ����
std::pair<point, int> findHashMap(int current, int depth, int alpha, int beta);

//��¼��ǰ����
void recordHashMap(int depth, hashFlag flag, int value, point move);

#endif
