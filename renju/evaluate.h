#ifndef _EVALUATE_
#define _EVALUATE_
//��ֵ������

extern const int cheng[6][3];

extern const int chong[6][3];

int Evaluate(int current); //�����ֵ�㷨�����ع�ֵ
int evaluate(int player, int current); // ��ĳһ���Ĺ�ֵ

// TODO: ����ͬʱ�������ӹ�ֵ��������������һ������һ�������ͬʱ�������Ӯ
int evaluateStep(int player, int x, int y); // ��ĳһ�����й�ֵ

#endif
