#pragma once

#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <unordered_map>
#include "common.h"

namespace HashMap {
	using std::min;
	using std::max;
	using std::vector;
	using std::make_pair;
	using std::pair;

	/******************************** define.h **************************************/

	int chessBoard[GRID_NUM][GRID_NUM];						//����
	int winner;												//��¼��Ϸ����ʱ��Ӯ�һ�ƽ��״̬
	int remainBlank = 225;											//�����е�ʣ����ÿ�λ
	std::vector<point> moveRecord;							//�����¼
	int agent;												//AI���ݵĽ�ɫ(����/����)
	int user;												//��Ұ��ݵĽ�ɫ(��AI�෴)
	int timeStamp;											//ʱ�������ǰ��ֲ�����

	/********************************* hash.h **************************************/

	typedef unsigned long long hash_t;

	const auto hashUnknowValue = (inf + 1);									//���ڱ�ʾ��ǰ�����Ƿ��ڹ�ϣ����

	hash_t zobristValue[GRID_NUM][GRID_NUM][3];				//ÿ��λ�õ�ÿ�����ӵ�zobristֵ
	hash_t whiteFirstValue, MinFirstValue;					//��ǰ�������к�������е�zobristֵ
	hash_t zobrist;											//��ǰ����zobristֵ������˭���֣�������min����max

	//�����������
	hash_t rand64() {
		return rand() ^ ((hash_t)rand() << 15) ^ ((hash_t)rand() << 30) ^ ((hash_t)rand() << 45) ^ ((hash_t)rand() << 60);
	}

	//hash�ڵ��еĹ�ֵ��ǩ������
	enum hashFlag { Exact, Lower, Upper };

	//��ϣ�ڵ�
	struct hashNode {
		hash_t zobrist;
		int depth;
		hashFlag flag;
		int value;
		point move;
		int time;
		hashNode() { }
		hashNode(hash_t zobrist, int depth, hashFlag flag, int value, point move, int time) :
			zobrist(zobrist), depth(depth), flag(flag), value(value), move(move), time(time) { }
	};
	std::unordered_map<hash_t, hashNode> hashMap;			//��ϣ��

	const auto HASH_CLEAN_TIME = 2;									//��ϣ�ڵ���ڵ�ʱ��
	//������δ�����ʵĹ�ϣ�ڵ�
	void hashMapClean()
	{
		for (auto iter = hashMap.begin(); iter != hashMap.end();) {
			if (timeStamp - iter->second.time > HASH_CLEAN_TIME)
				iter = hashMap.erase(iter);
			else
				iter++;
		}
	}

	//zobristֵ�ĳ�ʼ��
	void initHashValue() {
		for (int i = 1; i < GRID_NUM; i++)
			for (int j = 1; j < GRID_NUM; j++) {
				zobristValue[i][j][1] = rand64();
				zobristValue[i][j][2] = rand64();
			}
		whiteFirstValue = rand64();
		MinFirstValue = rand64();
		zobrist = 0;
		hashMap.clear();
	}

	/******************************** evaluate.h ***********************************/


//�����������͹�ֵ��
	const int cheng[6][3] = {
	{0,0,0},
	{0,0,0}, //�� 1
	{30,50,100}, // �� 2���������˫��
	{50,200,5000}, // �� 3
	{10,8000,500000}, // �� 4
	{10000000,10000000,10000000}
	};

	//��ϵ������͹�ֵ��
	const int chong[6][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,10,100}, // �� 3
	{0,50,5000}, // �� 4
	{20,200,8000} // �� 5
	};

	//���ֵ������������͹�ֵ��
	const int xianShouCheng[6][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,500000}, // ���ֳ�˫��3
	{0,500000,500000}, // ���ֳɻ�4 ��Ӯ
	{10000000,10000000,10000000},
	};

	//���ֵļ�ϵ������͹�ֵ��
	const int xianShouChong[6][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,2000,500000}, // ���ֳ�˫��4 ��Ӯ
	{10000000,10000000,10000000}, // ���ֳ� 5 ��Ӯ
	};

	//���ӵ���Դ�Ȩ�طֲ���
	const int PosValue[GRID_NUM][GRID_NUM] =
	{
		{0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		{0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0, 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0, 0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
		{0, 0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
		{0, 0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
		{0, 0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
		{0, 0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
		{0, 0,1,2,3,4,5,6,7,6,5,4,3,2,1,0},
		{0, 0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
		{0, 0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
		{0, 0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
		{0, 0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
		{0, 0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
		{0, 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	int evaluate(int player, int current);
	int evaluateStep(int player, int x, int y);
	int patternAnalysis(int chengCnt[6][3], int chongCnt[6][3]);

	//ȫ�ֹ�ֵ�㷨
	int Evaluate(int current) {
		int res = evaluate(agent, current) - evaluate(user, current);
		if (current == user) res -= 500;
		return res;
	}

	//��ĳһ�����о��������ֵ
	int evaluate(int player, int current)
	{
		const int n = GRID_NUM - 1;
		int eval = 0;
		int chengCnt[6][3]{}, chongCnt[6][3]{};

		// ˮƽ
		for (int i = 1; i <= n; i++) {
			int lastL = -1, lastR = -1;
			int lastLB = -1, lastRB = -1;
			for (int j = 1; j <= n; j++) {
				if (chessBoard[i][j] == player) {
					int l = j, r = j;
					while (r + 1 <= n && chessBoard[i][r + 1] == player) r++;
					// ��
					int leftUnblocked = !(l - 1 == 0 || chessBoard[i][l - 1] == opposite(player));
					int rightUnblocked = !(r + 1 == n + 1 || chessBoard[i][r + 1] == opposite(player));
					eval += cheng[min(r - l + 1, 5)][leftUnblocked + rightUnblocked];
					eval += (player == current) * xianShouCheng[min(r - l + 1, 5)][leftUnblocked + rightUnblocked];
					chengCnt[min((r - l + 1), 5)][leftUnblocked + rightUnblocked]++;
					// ��
					if (lastR != -1 && lastR == l - 2 && chessBoard[i][l - 1] == blank) {
						eval += chong[min(r - lastL + 1, 5)][lastLB + rightUnblocked];
						eval += (player == current) * xianShouChong[min(r - lastL + 1, 5)][lastLB + rightUnblocked];
						chongCnt[min(r - lastL + 1, 5)][lastLB + rightUnblocked]++;
					}
					lastL = l; lastR = r; lastLB = leftUnblocked; lastRB = rightUnblocked;
					j = r;
				}
			}
		}

		// ��ֱ
		for (int j = 1; j <= n; j++) {
			int lastL = -1, lastR = -1;
			int lastLB = -1, lastRB = -1;
			for (int i = 1; i <= n; i++) {
				if (chessBoard[i][j] == player) {
					int l = i, r = i;
					while (r + 1 <= n && chessBoard[r + 1][j] == player) r++;
					// ��
					int leftUnblocked = !(l - 1 == 0 || chessBoard[l - 1][j] == opposite(player));
					int rightUnblocked = !(r + 1 == n + 1 || chessBoard[r + 1][j] == opposite(player));
					eval += cheng[min(r - l + 1, 5)][leftUnblocked + rightUnblocked];
					eval += (player == current) * xianShouCheng[min(r - l + 1, 5)][leftUnblocked + rightUnblocked];
					chengCnt[min((r - l + 1), 5)][leftUnblocked + rightUnblocked]++;
					// ��
					if (lastR != -1 && lastR == l - 2 && chessBoard[l - 1][j] == blank) {
						eval += chong[min(r - lastL + 1, 5)][lastLB + rightUnblocked];
						eval += (player == current) * xianShouChong[min(r - lastL + 1, 5)][lastLB + rightUnblocked];
						chongCnt[min(r - lastL + 1, 5)][lastLB + rightUnblocked]++;
					}
					lastL = l; lastR = r; lastLB = leftUnblocked; lastRB = rightUnblocked;
					i = r;
				}
			}
		}

		// �L
		for (int s = 1 + 1; s <= n + n; s++) {
			int lastL = -1, lastR = -1;
			int lastLB = -1, lastRB = -1;
			int minJ = max(s - n, 1), maxJ = min(s - 1, n);
			for (int j = minJ; j <= maxJ; j++) {
				if (chessBoard[s - j][j] == player) {
					int l = j, r = j;
					while (r + 1 <= maxJ && chessBoard[s - (r + 1)][r + 1] == player) r++;
					// ��
					int leftUnblocked = !(l - 1 == minJ - 1 || chessBoard[s - (l - 1)][l - 1] == opposite(player));
					int rightUnblocked = !(r + 1 == maxJ + 1 || chessBoard[s - (r + 1)][r + 1] == opposite(player));
					eval += cheng[min(r - l + 1, 5)][leftUnblocked + rightUnblocked];
					eval += (player == current) * xianShouCheng[min(r - l + 1, 5)][leftUnblocked + rightUnblocked];
					chengCnt[min((r - l + 1), 5)][leftUnblocked + rightUnblocked]++;
					// ��
					if (lastR != -1 && lastR == l - 2 && chessBoard[s - (l - 1)][l - 1] == blank) {
						eval += chong[min(r - lastL + 1, 5)][lastLB + rightUnblocked];
						eval += (player == current) * xianShouChong[min(r - lastL + 1, 5)][lastLB + rightUnblocked];
						chongCnt[min(r - lastL + 1, 5)][lastLB + rightUnblocked]++;
					}
					lastL = l; lastR = r; lastLB = leftUnblocked; lastRB = rightUnblocked;
					j = r;
				}
			}
		}

		// �K
		for (int s = 1 - n; s <= n - 1; s++) {
			int lastL = -1, lastR = -1;
			int lastLB = -1, lastRB = -1;
			int minJ = max(1 - s, 1), maxJ = min(n - s, n);
			for (int j = minJ; j <= maxJ; j++) {
				if (chessBoard[s + j][j] == player) {
					int l = j, r = j;
					while (r + 1 <= maxJ && chessBoard[s + (r + 1)][r + 1] == player) r++;
					// ��
					int leftUnblocked = !(l - 1 == minJ - 1 || chessBoard[s + (l - 1)][l - 1] == opposite(player));
					int rightUnblocked = !(r + 1 == maxJ + 1 || chessBoard[s + (r + 1)][r + 1] == opposite(player));
					eval += cheng[min(r - l + 1, 5)][leftUnblocked + rightUnblocked];
					eval += (player == current) * xianShouCheng[min(r - l + 1, 5)][leftUnblocked + rightUnblocked];
					chengCnt[min((r - l + 1), 5)][leftUnblocked + rightUnblocked]++;
					// ��
					if (lastR != -1 && lastR == l - 2 && chessBoard[s + (l - 1)][l - 1] == blank) {
						eval += chong[min(r - lastL + 1, 5)][lastLB + rightUnblocked];
						eval += (player == current) * xianShouChong[min(r - lastL + 1, 5)][lastLB + rightUnblocked];
						chongCnt[min(r - lastL + 1, 5)][lastLB + rightUnblocked]++;
					}
					lastL = l; lastR = r; lastLB = leftUnblocked; lastRB = rightUnblocked;
					j = r;
				}
			}
		}
		return patternAnalysis(chengCnt, chongCnt) + eval;
	}

	constexpr int Dx[] = { 1,0,1,1 };						//�����������
	constexpr int Dy[] = { 0,1,1,-1 };

	//��ĳһ�����е������ӵĿ��ٹ�ֵ
	int evaluateStep(int player, int x, int y)
	{
		int chengCnt[6][3]{}, chongCnt[6][3]{};
		int eval = 0;
		for (int k = 0; k < 4; k++) {
			int dx = Dx[k], dy = Dy[k];
			int lx = x, ly = y, rx = x, ry = y;
			while (inboard(lx - dx, ly - dy) && chessBoard[lx - dx][ly - dy] == player)
				lx -= dx, ly -= dy;
			while (inboard(rx + dx, ry + dy) && chessBoard[rx + dx][ry + dy] == player)
				rx += dx, ry += dy;
			int leftUnblocked = !(!inboard(lx - dx, ly - dy) || chessBoard[lx - dx][ly - dy] == opposite(player));
			int rightUnblocked = !(!inboard(rx + dx, ry + dy) || chessBoard[rx + dx][ry + dy] == opposite(player));
			// ��
			eval += cheng[min(max(abs(rx - lx + 1), abs(ry - ly + 1)), 5)][leftUnblocked + rightUnblocked];
			chengCnt[min(max(abs(rx - lx + 1), abs(ry - ly + 1)), 5)][leftUnblocked + rightUnblocked]++;

			// ���
			if (!leftUnblocked && inboard(lx - 2 * dx, ly - 2 * dy) && chessBoard[lx - 2 * dx][ly - 2 * dy] == player) {
				int llx = lx - 2 * dx, lly = ly - 2 * dy;
				while (inboard(llx - dx, lly - dy) && chessBoard[llx - dx][lly - dy] == player)
					llx -= dx, lly -= dy;
				int leftLeftUnblocked = !(!inboard(llx - dx, lly - dy) || chessBoard[llx - dx][lly - dy] == opposite(player));
				eval += chong[min(max(abs(rx - llx + 1), abs(ry - lly + 1)), 5)][leftLeftUnblocked + rightUnblocked];
				chongCnt[min(max(abs(rx - llx + 1), abs(ry - lly + 1)), 5)][leftLeftUnblocked + rightUnblocked]++;
			}

			// �ҳ�
			if (!rightUnblocked && inboard(rx + 2 * dx, ry + 2 * dy) && chessBoard[rx + 2 * dx][ry + 2 * dy] == player) {
				int rrx = rx + 2 * dx, rry = ry + 2 * dy;
				while (inboard(rrx + dx, rry + dy) && chessBoard[rrx + dx][rry + dy] == player)
					rrx += dx, rry += dy;
				int rightRightUnblocked = !(!inboard(rrx + dx, rry + dy) || chessBoard[rrx + dx][rry + dy] == opposite(player));
				eval += chong[min(max(abs(rrx - lx + 1), abs(rry - ly + 1)), 5)][leftUnblocked + rightRightUnblocked];
				chongCnt[min(max(abs(rrx - lx + 1), abs(rry - ly + 1)), 5)][leftUnblocked + rightRightUnblocked];
			}
		}
		return patternAnalysis(chengCnt, chongCnt) + eval + PosValue[x][y];
	}

	//������͹�ֵ
	int patternAnalysis(int chengCnt[6][3], int chongCnt[6][3])
	{
		//��ʤ����
		int ret = 0, winMove = 0, goodTry = 0;
		winMove += chengCnt[4][2] + chengCnt[5][0] + chengCnt[5][1] + chengCnt[5][2];
		winMove += (chengCnt[3][2] > 1); //˫������
		winMove += ((chongCnt[5][0] + chongCnt[5][1] + chongCnt[5][2]) > 1); //˫������
		winMove += (chengCnt[3][2] && chengCnt[4][1]); //����+�������
		winMove += (chengCnt[4][1] && chongCnt[5][2]); //�����+��5�ͣ������������β���һ�𣬲��ᱻͬʱ���������ʤ
		ret += (!!winMove) * (winValue / 2);

		//׼��Ӯ��Ǳ������
		goodTry += 50 * (chengCnt[3][2] && chongCnt[5][2]); //����+��5��,��һ�����ʱ�������.OOO.O.��,�����Գ���
		goodTry += 30 * (chengCnt[3][2] && (chongCnt[5][1] || chongCnt[5][0])); //����+���5��
		goodTry += 25 * (chengCnt[4][1] && (chongCnt[5][1] || chongCnt[5][0])); //�����+��5�ͣ������ܱ�����

		//�Է���Ӧ
		goodTry += 100 * (chengCnt[3][2] + chongCnt[4][2]);
		goodTry += 100 * (chongCnt[5][0] + chongCnt[5][1]);
		ret += goodTry * 100;
		return ret;
	}

	/******************************* createmoves.h *********************************/

	const auto MOVE_NUM = 8U;											//������������֧��
	const auto DEFEND_NUM = 3U;											//��֤���ڷ��ز��Եķ�֧��

	//�Ѿ�ִ�й�createMoves�ľ��棬��¼����������ظ�
	std::unordered_map<hash_t, std::vector<point>> createdMoves;

	//������ѵ���չ������������
	//����˼�룺
	//��ÿ���Ϸ����ӵ���й��ۣ�
	//ѡȡ������ߵ����ӵ����������
	std::vector<point> createMoves(int player)
	{
		//��ֹ��ͬһ�����ظ�ִ�У����Ч��
		if (createdMoves.find(zobrist) != createdMoves.end()) return createdMoves[zobrist];

		int n = GRID_NUM - 1;
		int eval[GRID_NUM][GRID_NUM]{}, defend_eval[GRID_NUM][GRID_NUM]{};
		vector<point> moves, defends;

		//�������ӵ�
		//���������Щλ�����壬
		//�ͻ�ܿ����벻�����档
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (chessBoard[i][j] == blank) {
					defends.push_back(point(i, j));
					defend_eval[i][j] = evaluateStep(opposite(player), i, j);
				}
		sort(defends.begin(), defends.end(), [&](const point & A, const point & B) {
			return defend_eval[A.x][A.y] > defend_eval[B.x][B.y];
			});
		while (defends.size() > DEFEND_NUM) defends.pop_back();

		//�������ӵ�
		//�����������Լ�ʤ�������ӵ�
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (chessBoard[i][j] == blank &&
					find(defends.begin(), defends.end(), point(i, j)) == defends.end()) {
					moves.push_back(point(i, j));
					eval[i][j] = evaluateStep(player, i, j);
				}
		sort(moves.begin(), moves.end(), [&](const point & A, const point & B) {
			return eval[A.x][A.y] > eval[B.x][B.y];
			});
		while (moves.size() > (MOVE_NUM - DEFEND_NUM)) moves.pop_back();

		//�ϲ������ͷ���
		for (auto it : defends) {
			moves.push_back(it);
			eval[it.x][it.y] = defend_eval[it.x][it.y];
		}
		sort(moves.begin(), moves.end(), [&](const point & A, const point & B) {
			return eval[A.x][A.y] > eval[B.x][B.y];
			});
		createdMoves[zobrist] = moves;
		return moves;
	}

	/******************************** gameover.h ***********************************/

	//�����ж��Ƿ���Ϸ������������ pos ��һ����Ӱ�죩������Ӯ����ƽ��
	//���� posλ��ȷΪ player���������
	int gameover(point pos, int player)
	{
		//���� player ���Ƿ�����pos��һ��ʤ��
		for (int k = 0; k < 4; k++) {
			int dx = Dx[k], dy = Dy[k];
			for (int start = -4; start <= 0; start++) {
				bool same = 1;
				for (int v = start; v < start + 5; v++)
					same &= (inboard(pos.x + dx * v, pos.y + dy * v) && chessBoard[pos.x + dx * v][pos.y + dy * v] == chessBoard[pos.x][pos.y]);
				if (same)
					return player;
			}
		}
		// �����Ƿ�ƽ��
		if (!remainBlank) { return draw; }
		return blank;
	}

	//����������Ϸ����ʱ��״̬
	int gameover()
	{
		if (!remainBlank) return draw; //ƽ��
		for (int i = 1; i < GRID_NUM; i++) {
			for (int j = 1; j < GRID_NUM; j++) {
				if (chessBoard[i][j] == blank)
					continue;
				for (int k = 0; k < 4; k++) {
					bool same = 1; int dx = Dx[k], dy = Dy[k];
					for (int v = -2; v <= 2; v++)
						same &= (inboard(i + dx * v, j + dy * v) && chessBoard[i + dx * v][j + dy * v] == chessBoard[i][j]);
					if (same)
						return chessBoard[i][j]; //ĳһ��ʤ���ļ���
				}
			}
		}
		return blank;
	}

	/******************************** makemove.h ***********************************/

	bool makeMove(point pos, int player);

	//ִ���߷�
	bool makeMove(int x, int y, int player)
	{
		return makeMove(point(x, y), player);
	}

	//ִ���߷�
	bool makeMove(point pos, int player)
	{
		if (chessBoard[pos.x][pos.y] != blank) return false;
		chessBoard[pos.x][pos.y] = player;
		zobrist ^= zobristValue[pos.x][pos.y][player];
		zobrist ^= whiteFirstValue;
		zobrist ^= MinFirstValue;
		moveRecord.push_back(pos);
		remainBlank--;
		return true;
	}

	//�����߷�
	bool unMakeMove(int player)
	{
		point pos = moveRecord.back();
		moveRecord.pop_back();
		zobrist ^= zobristValue[pos.x][pos.y][player];
		zobrist ^= whiteFirstValue;
		zobrist ^= MinFirstValue;
		chessBoard[pos.x][pos.y] = blank;
		remainBlank++;
		return true;
	}

	/******************************* searchmove.h **********************************/

	const auto SEARCH_DEPTH = (10);										//�ο�������������

	std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta);
	std::pair<point, int> findHashMap(int current, int depth, int alpha, int beta);
	void recordHashMap(int depth, hashFlag flag, int value, point move);

	int searchCount = 0;

	double branchFact[20]; // ��ƽ������Ч��֧����b��1+b+b^2+...b^d = N�������ڵ�����
	int branchFactCount[20];

	//��������ں���
	std::pair<point, int> searchMove(int depth = SEARCH_DEPTH)
	{
		hashMap.clear();
		printf("������ȣ�%d\n", depth);
		searchCount = 0;
		auto result = MiniMax(agent, depth, -inf, inf);
		double b = solveBranchFact(depth, searchCount);
		branchFact[depth] = (branchFact[depth] * branchFactCount[depth] + b) / (branchFactCount[depth] + 1);
		branchFactCount[depth]++;
		return result;
	}

	//��alpha-beta��֦��Minimax�����㷨
	//current : ��ǰ player
	std::pair<point, int> MiniMax(int current, int depth, int alpha, int beta) {

		//���ҵ�ǰ�����Ƿ��ڹ�ϣ���У��Լ�������
		std::pair<point, int> hashResult = findHashMap(current, depth, alpha, beta);
		if (hashResult.second != hashUnknowValue) {
			return hashResult;
		}
		searchCount++;

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

	/********************************* clearall ************************************/

	void clearAll() {
#define cl(x) memset(x,0,sizeof(x))

		cl(chessBoard);
		winner = 0;											//��¼��Ϸ����ʱ��Ӯ�һ�ƽ��״̬
		remainBlank = 225;											//�����е�ʣ����ÿ�λ
		moveRecord.clear();							//�����¼
		agent = 0;												//AI���ݵĽ�ɫ(����/����)
		user = 0;												//��Ұ��ݵĽ�ɫ(��AI�෴)
		timeStamp = 0;											//ʱ�������ǰ��ֲ�����

		cl(zobristValue);				//ÿ��λ�õ�ÿ�����ӵ�zobristֵ
		whiteFirstValue = MinFirstValue = 0;					//��ǰ�������к�������е�zobristֵ
		zobrist = 0;											//��ǰ����zobristֵ������˭���֣�������min����max
		hashMap.clear();

		createdMoves.clear();

		cl(branchFact);
		cl(branchFactCount);

#undef cl
	}
}