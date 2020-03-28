#include "define.h"
#include "createmoves.h"
#include "makemove.h"
#include "evaluate.h"
#include "printchessboard.h"
#include "searchmove.h"
#include <algorithm>
#include <cassert>
#include <cmath>
using namespace std;

std::pair<point, int> searchMove()
{
	return idSearch();
}

static int ran01() { static int x = 31253125; x += (x << 4) + 1; return x & 65536; }

std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta) {
	std::pair<point, int> hashResult = findHashMap(current, depth, alpha, beta);
	if (hashResult.second != hashUnknowValue) {
		/*if (depth > 2) {
			++hashSuccess;
			if (hashSuccess % 100 == 0) {
				cerr << "Hash Success: " << hashSuccess << endl;
			}
		}*/
		return hashResult;
	}
	point hashGivenMove = hashResult.first;

	if (depth == 0) {
		int v = Evaluate(current);
		recordHashMap(depth, Exact, v, point());
		return make_pair(point(), v);
	}

	vector<point> moveList = createMoves(current, idDepth - depth);
	int exploreLen = moveList.size();

	if (current == agent) { // 极大搜索
		point optMove;
		int v = -inf, newv;
		for (int i = -1; i < exploreLen; i++) {
			point currentMove = i == -1 ? hashGivenMove : moveList[i];
			if (currentMove == point() || (i >= 0 && currentMove == hashGivenMove))
				continue;

			if (makeMove(currentMove, current)) {
				if (gameover(currentMove, current))
					newv = winValue;
				else
					newv = MiniMax(opposite(current), depth - 1, alpha, beta).second;
				if (newv > v || (newv == v && ran01())) // 增加随机性
				//if (newv > v)
					v = newv, optMove = currentMove;
					currentBest[(long long)idDepth - depth] = currentMove;
				if (v >= beta) {
					unMakeMove(current);
					recordHashMap(depth, Upper, v, optMove);
					return make_pair(optMove, v);
				}
				alpha = max(alpha, v);
				unMakeMove(current);
			}
		}

		recordHashMap(depth, Exact, v, optMove);
		return make_pair(optMove, v);
	}
	else { // 极小搜索
		point optMove;
		int v = inf, newv;
		for (int i = -1; i < exploreLen; i++) {
			point currentMove = i == -1 ? hashGivenMove : moveList[i];
			if (currentMove == point() || (i >= 0 && currentMove == hashGivenMove))
				continue;

			if (makeMove(currentMove, current)) {
				if (gameover(currentMove, current))
					newv = -(int)(winValue * pow(0.95, (SEARCH_DEPTH - depth) >> 1)); // 考虑玩家是非理性人，算力有限
				else
					newv = MiniMax(opposite(current), depth - 1, alpha, beta).second;
				if (newv < v || (newv == v && ran01())) // 增加随机性
				//if (newv < v)
					v = newv, optMove = currentMove;
					currentBest[(long long)idDepth - depth] = currentMove;
				if (v <= alpha) {
					unMakeMove(current);
					recordHashMap(depth, Lower, v, optMove);
					return make_pair(optMove, v);
				}
				beta = min(beta, v);
				unMakeMove(current);
			}
		}

		recordHashMap(depth, Exact, v, optMove);
		return make_pair(optMove, v);
	}
}

std::pair<point, int> findHashMap(int current, int depth, int alpha, int beta) {
	if (hashMap.find(zobrist) == hashMap.end()) return std::make_pair(point(), hashUnknowValue);
	hashNode node = hashMap[zobrist];
	if (node.depth >= depth) {
		if (node.flag == Exact)
			return make_pair(node.move, node.value);
		if (current == agent) { // MAX
			if (node.flag == Upper && node.value >= beta)
				return make_pair(node.move, node.value);
		}
		else { // MIN
			if (node.flag == Lower && node.value <= alpha)
				return make_pair(node.move, node.value);
		}
	}
	return std::make_pair(node.move, hashUnknowValue);
}

std::pair<point, int> idSearch(int depth, unsigned timeout)
{
	unsigned total = 0, pre = 0;
	std::pair<point, int> res;
	currentBest.clear();
	for (int i = 1; i <= depth; i++)
	{
		idDepth = i;
		currentBest.push_back(point());
		hashMap.clear();
		pre = clock();
		res = MiniMax(agent, i, -inf, inf);
		if (res.second >= winValue) return res;
		currentBest[(long long)i - 1] = res.first;
		total += clock() - pre;
		if (total >= timeout) break;
	}
	return res;
}

void recordHashMap(int depth, hashFlag flag, int value, point move) {
	if (hashMap.find(zobrist) == hashMap.end() || hashMap[zobrist].depth < depth ||
		(hashMap[zobrist].depth == depth && flag == Exact)) {
		hashMap[zobrist] = hashNode(zobrist, depth, flag, value, move);
	}
}

point randomMove() {
	while (true) {
		int x = rand() % (GRID_NUM - 1) + 1;
		int y = rand() % (GRID_NUM - 1) + 1;
		if (chessBoard[x][y] == blank) return point(x, y);
	}
}
