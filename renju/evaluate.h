#ifndef _EVALUATE_
#define _EVALUATE_
//��ֵ������

extern const int cheng[6][3];									//�����������͹�ֵ��
extern const int chong[6][3];									//��ϵ������͹�ֵ��

//ȫ�ֹ�ֵ�㷨
int Evaluate(int current); 

//��ĳһ�����о��������ֵ
int evaluate(int player, int current);

//��ĳһ�����е������ӵĿ��ٹ�ֵ
int evaluateStep(int player, int x, int y);

//������͹�ֵ
int patternAnalysis(int chengCnt[6][3], int chongCnt[6][3]);

#endif
