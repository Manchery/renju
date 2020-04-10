#include "define.h"
#include "createmoves.h"
#include "evaluate.h"
#include <algorithm>
using namespace std;

std::unordered_map<hash_t, std::vector<point>> createdMoves;

std::vector<point> createMoves(int player)
{
	// 为了效率，hash表中存储的行动优先扩展的相关代码被揉到 MiniMax 函数里面了
	if (createdMoves.find(zobrist) != createdMoves.end()) return createdMoves[zobrist];
	int n = GRID_NUM - 1;
	int eval[GRID_NUM][GRID_NUM];
	vector<point> moves, defends;

	//defends
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (chessBoard[i][j] == blank) {
				defends.push_back(point(i, j));
				eval[i][j] = evaluateStep(opposite(player), i, j);
			}
	sort(defends.begin(), defends.end(), [&](const point& A, const point& B) {
		return eval[A.x][A.y] > eval[B.x][B.y];
		});
	while (defends.size() > DEFEND_NUM) defends.pop_back();

	//attacks + minimax
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (chessBoard[i][j] == blank) {
				moves.push_back(point(i, j));
				eval[i][j] = evaluateStep(player, i, j);
			}
	sort(moves.begin(), moves.end(), [&](const point &A, const point &B) {
		return eval[A.x][A.y] > eval[B.x][B.y];
	});
	while (moves.size() > (MOVE_NUM - 2)) moves.pop_back();

	//merge
	for (auto it : defends)
	{
		moves.push_back(it);
	}
	sort(moves.begin(), moves.end(), [&](const point& A, const point& B) {
		return eval[A.x][A.y] > eval[B.x][B.y];
	});
	createdMoves[zobrist] = moves;
	return moves;
}

//查找估值较高的合法落子点。
