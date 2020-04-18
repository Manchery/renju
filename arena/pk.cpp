#include "AlphaBeta.h"
#include "HashMap.h"
#include "IDSearch.h"
#include <cstring>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cassert>
#include <windows.h>
using namespace std;
#define cl(x) memset(x,0,sizeof(x));

int chessBoard[GRID_NUM][GRID_NUM];
int remainBlank;

//��ӡ����
void print();
int gameover();
void Print(int round, int blackWin, int whiteWin, string blackName, string whiteName, int current);

#define AgentBlack AlphaBeta
string blackName("AlphaBeta");
#define AgentWhite IDSearch
string whiteName("IDSearch");
const int Round = 10;

int main() {
	srand(time(0));
	int blackWin = 0, whiteWin = 0; int winner;
	for (int i = 1; i <= Round; i++) {
		cl(chessBoard); remainBlank = 225;
		AgentBlack::clearAll(); AgentBlack::initHashValue();
		AgentWhite::clearAll(); AgentWhite::initHashValue();
		AgentBlack::agent = AgentWhite::user = black;
		AgentWhite::agent = AgentBlack::user = white;
		AgentWhite::zobrist ^= AgentWhite::MinFirstValue;
		while (true) {
			Print(i, blackWin, whiteWin, blackName, whiteName, black);
			point blackPos = AgentBlack::searchMove().first;
			if (chessBoard[blackPos.x][blackPos.y] != blank) {
				cout << "�ڷ����ӷǷ�" << endl; system("pause"); return 0;
			}
			chessBoard[blackPos.x][blackPos.y] = black; remainBlank--;
			AgentBlack::makeMove(blackPos, AgentBlack::agent);
			AgentWhite::makeMove(blackPos, AgentBlack::user);
			if (winner = gameover()) {
				if (winner == black) blackWin++;
				printf("��ʤ\n");
				Sleep(10000);
				break;
			}

			Print(i, blackWin, whiteWin, blackName, whiteName, white);
			point whitePos = AgentWhite::searchMove().first;
			if (chessBoard[whitePos.x][whitePos.y] != blank) {
				cout << "�׷����ӷǷ�" << endl; system("pause"); return 0;
			}
			chessBoard[whitePos.x][whitePos.y] = white; remainBlank--;
			AgentWhite::makeMove(whitePos, AgentBlack::agent);
			AgentBlack::makeMove(whitePos, AgentBlack::user);
			if (winner = gameover()) {
				if (winner == white) whiteWin++;
				printf("��ʤ\n");
				Sleep(10000);
				break;
			}
		}
	}
	printf("�Ծ���ϣ��ڷ���ʤ:�׷���ʤ:ƽ�� = %d:%d:%d\n", blackWin, whiteWin, Round - blackWin - whiteWin);
	system("pause");
	return 0;
}

void Print(int round, int blackWin, int whiteWin, string blackName, string whiteName, int current) {
	system("cls");
	cout << "�ڷ���" << blackName << "���׷���" << whiteName << endl;
	printf("�� %d/%d ��\n�ڷ���ʤ:�׷���ʤ:ƽ�� = %d:%d:%d\n", round, Round, blackWin, whiteWin, round - 1 - blackWin - whiteWin);
	print();
	cout << (current == black ? "����" : "����") << "˼����..." << endl;
}

//����������״
void judge(int i, int j)
{
	if (i == 1 && j == 1)
		printf("�X ");
	else if (i == 1 && j == 15)
		printf("�[");
	else if (i == 15 && j == 1)
		printf("�^ ");
	else if (i == 15 && j == 15)
		printf("�a");
	else if (i == 1 && j != 15 && j != 1)
		printf("�� ");
	else if (i == 15 && j != 15 && j != 1)
		printf("�� ");
	else if (j == 1 && i != 15 && i != 1)
		printf("�� ");
	else if (j == 15 && i != 15 && i != 1)
		printf("��");
	else
		printf("�� ");
}

//��ӡ����
void print()
{
	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			printf("  ");
			for (int j = 1; j < 16; j++)
				printf("%-2d", j);
			printf("\n");
			continue;
		}
		for (int j = 0; j < 16; j++)
		{
			if (j == 0)
			{
				printf("%2d", i);
				continue;
			}

			if (chessBoard[i][j] == 1) //�˴�Ϊ����
				printf("��");
			else if (chessBoard[i][j] == 2) //�˴�Ϊ����
				printf("��");
			else
			{
				judge(i, j);
			}
		}
		printf("\n");
	}
}

static constexpr int Dx[] = { 1,0,1,1 };						//���ӷ���
static constexpr int Dy[] = { 0,1,1,-1 };

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
