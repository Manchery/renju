#ifndef _EVALUATE_
#define _EVALUATE_

#include "define.h"

extern const int cheng[6][3];									//�����������͹�ֵ��"��"��
extern const int chong[6][3];									//��ϵ������͹�ֵ��"��"��
extern const int xianShouCheng[6][3];							//���ֵ������������͹�ֵ��
extern const int xianShouChong[6][3];							//���ֵļ�ϵ������͹�ֵ��

extern const int PosValue[GRID_NUM][GRID_NUM];					//���ӵ���Դ�Ȩ�طֲ���

//ȫ�ֹ�ֵ�㷨
int Evaluate(int current); 

//��ĳһ�����о��������ֵ
int evaluate(int player, int current);

//��ĳһ�����е������ӵĿ��ٹ�ֵ
int evaluateStep(int player, int x, int y);

//������͹�ֵ
int patternAnalysis(int chengCnt[6][3], int chongCnt[6][3]);

#endif
