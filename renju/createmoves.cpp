#include "define.h"
#include "createmoves.h"
#include "evaluate.h"
#include <algorithm>
using namespace std;

//搜索队列
std::unordered_map<hash_t, std::vector<point>> createdMoves;

//生成最佳的搜索队列
//基本思想：
//对每个合法落子点进行估价，
//选取估价最高的落子点进行搜索。
std::vector<point> createMoves(int player)
{
	//根据迭代搜索上一次的搜索结果
	//指导这一次的搜索顺序
	if (createdMoves.find(zobrist) != createdMoves.end()) return createdMoves[zobrist];
	int n = GRID_NUM - 1;
	int eval[GRID_NUM][GRID_NUM];
	vector<point> moves, defends;

	//防守落子点
	//如果不在这些位置下棋，
	//就会很快陷入不利局面。
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

	//进攻落子点
	//搜索有利于自己胜利的落子点
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (chessBoard[i][j] == blank) {
				moves.push_back(point(i, j));
				eval[i][j] = evaluateStep(player, i, j);
			}
	sort(moves.begin(), moves.end(), [&](const point &A, const point &B) {
		return eval[A.x][A.y] > eval[B.x][B.y];
	});
	while (moves.size() > (MOVE_NUM - DEFEND_NUM)) moves.pop_back();

	//合并搜索队列
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
