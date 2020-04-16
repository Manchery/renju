#include "evaluate.h"
#include <algorithm>
#include <cmath>
using namespace std;

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

//ȫ�ֹ�ֵ�㷨
int Evaluate(int current) {
	int res = evaluate(agent, current) - evaluate(user, current);
	if (current == user) res -= 500;
	return res;
}

//��ĳһ�����о��������ֵ
int evaluate(int player, int current)
{
	const int n = GRID_NUM-1;
	int eval = 0;
	int chengCnt[6][3]{}, chongCnt[6][3]{};
	
	// ˮƽ
	for (int i = 1; i <= n; i++) {
		int lastL = -1, lastR = -1;
		int lastLB = -1, lastRB = -1;
		for (int j = 1; j <= n;j++) {
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

static constexpr int Dx[] = { 1,0,1,1 };						//�����������
static constexpr int Dy[] = { 0,1,1,-1 };

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