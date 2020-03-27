#include "define.h"
#include "createmoves.h"
#include "evaluate.h"
#include <algorithm>
using namespace std;

void createMoves(int player, std::vector<point>& moveSorted) //生成全部合法走法集
{
	int n = GRID_NUM - 1;
	int eval[GRID_NUM][GRID_NUM];
	moveSorted.clear();
	for (int i=1;i<=n;i++)
		for (int j = 1; j <= n; j++)
			if (chessBoard[i][j] == blank) {
				moveSorted.push_back(point(i, j));
				eval[i][j] = max(evaluateStep(black, i, j), evaluateStep(white, i, j));
			}
	sort(moveSorted.begin(), moveSorted.end(), [&](const point &A, const point &B) {
		return eval[A.x][A.y] > eval[B.x][B.y];
	});
}
//查找所有合法落子点。对于五子棋来说，棋盘上的空白点均为可行走法。
