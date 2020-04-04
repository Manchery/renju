#ifndef _EVALUATE_
#define _EVALUATE_
//估值生成器

extern const int cheng[6][3];

extern const int chong[6][3];

int Evaluate(int current); //局面估值算法，返回估值
int evaluate(int player, int current); // 对某一方的估值

// TODO: 棋形同时存在增加估值：如两个活三、一个活三一个半活四同时存在则必赢
// TODO: 两个空格(XOO.O..OO)或其它复杂棋型(.O.O.O.O.)等的判断，它们都是对手必应棋型或潜力棋型，
//		 考虑直接特判？
int evaluateStep(int player, int x, int y); // 对某一步进行估值
int patternAnalysis(int chengCnt[6][3], int chongCnt[6][3]); // 组合棋型分析

#endif
