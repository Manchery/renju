#include "define.h"
#include "createmoves.h"
#include "evaluate.h"
#include <algorithm>
using namespace std;

std::unordered_map<hash_t, std::vector<point>> createdMoves;

std::vector<point> createMoves(int player, int depth)
{
	if (createdMoves.find(zobrist) != createdMoves.end()) return createdMoves[zobrist];
	int n = GRID_NUM - 1;
	int eval[GRID_NUM][GRID_NUM];
	vector<point> moves, defends;

	//�鿴�Ƿ�����Ҫ���ص����
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (chessBoard[i][j] == blank) {
				defends.push_back(point(i, j));
				eval[i][j] = evaluateStep(opposite(player), i, j);
			}
	sort(defends.begin(), defends.end(), [&](const point& A, const point& B) {
		return eval[A.x][A.y] > eval[B.x][B.y];
		});
	while (defends.size() > MOVE_NUM / 2) defends.pop_back();

	//�����������+������һ��Minimax�Ľ�ȷ����������˳��
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (chessBoard[i][j] == blank) {
				moves.push_back(point(i, j));
				eval[i][j] = evaluateStep(player, i, j);
			}
	if (depth < currentBest.size())
	{
		auto& p = currentBest[depth];
		eval[p.x][p.y] += winValue;
	}
	sort(moves.begin(), moves.end(), [&](const point &A, const point &B) {
		return eval[A.x][A.y] > eval[B.x][B.y];
	});
	while (moves.size() > MOVE_NUM / 2) moves.pop_back();

	//�ϲ����������б�
	for (auto it : defends)
	{
		moves.push_back(it);
	}
	createdMoves[zobrist] = moves;
	return moves;
}
//�������кϷ����ӵ㡣������������˵�������ϵĿհ׵��Ϊ�����߷���
