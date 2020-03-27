#include "define.h"
#include "createmoves.h"
#include "evaluate.h"
#include <algorithm>
using namespace std;

void createMoves(int player, std::vector<point>& moveSorted) //����ȫ���Ϸ��߷���
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
//�������кϷ����ӵ㡣������������˵�������ϵĿհ׵��Ϊ�����߷���
