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

//��������ں���
std::pair<point, int> searchMove()
{
	//���ڱ�Ӧ���ͽ��п��ٷ���
	auto res = fastDefend();
	if (!(res.first == point())) return res;

	//������������
	return idSearch();
}


//��alpha-beta��֦��Minimax�����㷨
//current : ��ǰ player
std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta) {

	//���ҵ�ǰ�����Ƿ��ڹ�ϣ���У��Լ�������
	std::pair<point, int> hashResult = findHashMap(current, depth, alpha, beta);
	if (hashResult.second != hashUnknowValue) {
		return hashResult;
	}

	//������ȴﵽ����ʱ���������沢����
	if (depth == 0) {
		int v = Evaluate(current);
		recordHashMap(depth, Exact, v, point());
		return make_pair(point(), v);
	}

	//��һ������ʱ�����ڹ�ϣ���е��ж���������
	point priorMove = hashResult.first;
	// ���ɴ���������չ��
	vector<point> moveList = createMoves(current);
	int exploreLen = moveList.size();
	int tmpWinner;

	if (current == agent) { // ��������
		point optMove;
		int v = -inf, newv;
		for (int i = -1; exploreLen && i < (int)moveList.size(); i++) { // i==-1 �������� priorMove
			point currentMove = i == -1 ? priorMove : moveList[i];
			if (currentMove == point() || (i >= 0 && currentMove == priorMove))
				continue;
			exploreLen--;

			if (makeMove(currentMove, current)) {
				if (tmpWinner = gameover(currentMove, current))
					newv = tmpWinner == current ? winValue : 0;
				else
					newv = MiniMax(opposite(current), depth - 1, alpha, beta).second;
				if (newv > v)
				{
					v = newv, optMove = currentMove;
				}
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
	else { // ��С����
		point optMove;
		int v = inf, newv;
		for (int i = -1; exploreLen && i < (int)moveList.size(); i++) { // i==-1 �������� priorMove
			point currentMove = i == -1 ? priorMove : moveList[i];
			if (currentMove == point() || (i >= 0 && currentMove == priorMove))
				continue;
			exploreLen--;

			if (makeMove(currentMove, current)) {
				if (tmpWinner = gameover(currentMove, current))
					// ��������Ƿ������ˣ���������
					newv = tmpWinner == current ? (-(int)(winValue * pow(0.95, (SEARCH_DEPTH - depth) >> 1))) : 0;
				else
					newv = MiniMax(opposite(current), depth - 1, alpha, beta).second;
				if (newv < v)
				{
					v = newv, optMove = currentMove;
				}
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


//������������
std::pair<point, int> idSearch(unsigned timeout, int depth)
{
	clock_t pre = clock();
	std::pair<point, int> res;
	long long startDepth = 1;

	//һ�����ܵ��Ż���
	//�Ӹþ�����ǰ�ﵽ���������ȿ�ʼ����
	if (hashMap.find(zobrist) != hashMap.end()) {
		startDepth = (long long)hashMap[zobrist].depth + 1;
		hashMap[zobrist].time = timeStamp;
	}

	hashMapClean();
	//��������������ֱ���ľ�ʱ��
	for (long long i = startDepth; ; i++)
	{
		res = MiniMax(agent, i, -inf, inf);
		if (res.second >= winValue) return res;
		if (clock() - pre >= timeout) break;
	}
	return res;
}

//���ٷ���
std::pair<point, int> fastDefend()
{
	int eval = evaluate(user, user);

	//�����˱�Ӧ����
	//���ȡ��С���������ֲ���
	if (eval >= 500000)
	{
		int minDamage = eval, curDamage = 0, agentEval = 0;
		point defendMove = point();
		for(int i = 1; i < GRID_NUM; i++)
			for (int j = 1; j < GRID_NUM; j++)
			{
				if (chessBoard[i][j] != blank) continue;
				makeMove(point(i, j), agent);
				curDamage = evaluate(user, user);
				if (curDamage < minDamage)
				{
					minDamage = curDamage;
					agentEval = evaluate(agent, user);
					defendMove = point(i, j);
				}
				else if (curDamage == minDamage)
				{
					auto curAgentEval = evaluate(agent, user);
					if ((defendMove == point()) ||
						(curAgentEval > agentEval))
					{
						minDamage = curDamage;
						agentEval = curAgentEval;
						defendMove = point(i, j);
					}
				}
				unMakeMove(agent);
			}
		return std::pair<point, int>(defendMove, Evaluate(agent));
	}

	//δ���ֱ�Ӧ����
	return std::pair<point, int>(point(), 0);
}


//���ҵ�ǰ����
std::pair<point, int> findHashMap(int current, int depth, int alpha, int beta) {
	if (hashMap.find(zobrist) == hashMap.end()) return std::make_pair(point(), hashUnknowValue);
	hashNode & node = hashMap[zobrist];
	node.time = timeStamp;
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

//��¼��ǰ����
void recordHashMap(int depth, hashFlag flag, int value, point move) {
	if (hashMap.find(zobrist) == hashMap.end() || hashMap[zobrist].depth < depth ||
		(hashMap[zobrist].depth == depth && flag == Exact)) {
		hashMap[zobrist] = hashNode(zobrist, depth, flag, value, move, timeStamp);
	}
}