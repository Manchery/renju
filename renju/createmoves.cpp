#include "define.h"
#include "createmoves.h"
#include "evaluate.h"
#include <algorithm>
using namespace std;

std::unordered_map<hash_t, std::vector<point>> createdMoves;

std::vector<point> createMoves(int player)
{
	if (createdMoves.find(zobrist) != createdMoves.end()) return createdMoves[zobrist];
	int n = GRID_NUM - 1;
	int eval[GRID_NUM][GRID_NUM];
	vector<point> moves;
	for (int i=1;i<=n;i++)
		for (int j = 1; j <= n; j++)
			if (chessBoard[i][j] == blank) {
				moves.push_back(point(i, j));
				eval[i][j] = max(evaluateStep(black, i, j), evaluateStep(white, i, j));
			}
	sort(moves.begin(), moves.end(), [&](const point &A, const point &B) {
		return eval[A.x][A.y] > eval[B.x][B.y];
	});
	while (moves.size() > MOVE_NUM) moves.pop_back();
	createdMoves[zobrist] = moves;
	return moves;
}
//�������кϷ����ӵ㡣������������˵�������ϵĿհ׵��Ϊ�����߷���
