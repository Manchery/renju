#include "define.h"
#include "createmoves.h"
#include "makemove.h"
#include "evaluate.h"
#include "printchessboard.h"
#include "searchmove.h"
#include <algorithm>
using namespace std;

point searchMove()
{
	return MiniMax(agent, 5, -inf, inf).first;
}

std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta) {
	if (depth == 0) return make_pair(point(), Evaluate(current));
	vector<point> moveList;
	createMoves(current, moveList);
	int exploreLen = min(5U, moveList.size());
	if (current == agent) { // 极大搜索
		point optMove;
		int v = -inf, newv;
		for (int i = 0; i < exploreLen; i++) {
			makeMove(moveList[i], current);
			if (gameover(moveList[i], current))
				newv = winValue;
			else
				newv = MiniMax(opposite(current), depth - 1, alpha, beta).second;
			if (newv>v)
				v = newv, optMove = moveList[i];
			if (v >= beta) {
				unMakeMove(current); 
				return make_pair(optMove, v);
			}
			alpha = max(alpha, v);
			unMakeMove(current);
		}
		return make_pair(optMove, v);
	}
	else { // 极小搜索
		point optMove;
		int v = inf, newv;
		for (int i = 0; i < exploreLen; i++) {
			makeMove(moveList[i], current);
			if (gameover(moveList[i], current))
				newv = -winValue;
			else
				newv = MiniMax(opposite(current), depth - 1, alpha, beta).second;
			if (newv < v)
				v = newv, optMove = moveList[i];
			if (v <= alpha) {
				unMakeMove(current);
				return make_pair(optMove, v);
			}
			beta = min(beta, v);
			unMakeMove(current);
		}
		return make_pair(optMove, v);
	}
}

point randomMove() {
	while (true) {
		int x = rand() % (GRID_NUM - 1) + 1;
		int y = rand() % (GRID_NUM - 1) + 1;
		if (chessBoard[x][y] == blank) return point(x, y);
	}
}
