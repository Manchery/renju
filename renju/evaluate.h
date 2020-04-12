#ifndef _EVALUATE_
#define _EVALUATE_
//估值生成器

extern const int cheng[6][3];									//连续单线棋型估值表
extern const int chong[6][3];									//间断单线棋型估值表

//全局估值算法
int Evaluate(int current); 

//对某一方进行局面整体估值
int evaluate(int player, int current);

//对某一方进行单步落子的快速估值
int evaluateStep(int player, int x, int y);

//组合棋型估值
int patternAnalysis(int chengCnt[6][3], int chongCnt[6][3]);

#endif
