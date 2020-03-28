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

	//查看是否有需要防守的情况
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

	//检测进攻的情况+根据上一次Minimax的解确定优先搜索顺序
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

	//合并两个搜索列表
	for (auto it : defends)
	{
		moves.push_back(it);
	}
	createdMoves[zobrist] = moves;
	return moves;
}
//查找所有合法落子点。对于五子棋来说，棋盘上的空白点均为可行走法。
