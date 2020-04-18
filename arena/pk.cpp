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

//打印棋盘
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
				cout << "黑方落子非法" << endl; system("pause"); return 0;
			}
			chessBoard[blackPos.x][blackPos.y] = black; remainBlank--;
			AgentBlack::makeMove(blackPos, AgentBlack::agent);
			AgentWhite::makeMove(blackPos, AgentBlack::user);
			if (winner = gameover()) {
				if (winner == black) blackWin++;
				printf("黑胜\n");
				Sleep(10000);
				break;
			}

			Print(i, blackWin, whiteWin, blackName, whiteName, white);
			point whitePos = AgentWhite::searchMove().first;
			if (chessBoard[whitePos.x][whitePos.y] != blank) {
				cout << "白方落子非法" << endl; system("pause"); return 0;
			}
			chessBoard[whitePos.x][whitePos.y] = white; remainBlank--;
			AgentWhite::makeMove(whitePos, AgentBlack::agent);
			AgentBlack::makeMove(whitePos, AgentBlack::user);
			if (winner = gameover()) {
				if (winner == white) whiteWin++;
				printf("白胜\n");
				Sleep(10000);
				break;
			}
		}
	}
	printf("对局完毕，黑方已胜:白方已胜:平局 = %d:%d:%d\n", blackWin, whiteWin, Round - blackWin - whiteWin);
	system("pause");
	return 0;
}

void Print(int round, int blackWin, int whiteWin, string blackName, string whiteName, int current) {
	system("cls");
	cout << "黑方：" << blackName << "；白方：" << whiteName << endl;
	printf("第 %d/%d 局\n黑方已胜:白方已胜:平局 = %d:%d:%d\n", round, Round, blackWin, whiteWin, round - 1 - blackWin - whiteWin);
	print();
	cout << (current == black ? "黑棋" : "白棋") << "思考中..." << endl;
}

//生成棋盘形状
void judge(int i, int j)
{
	if (i == 1 && j == 1)
		printf("╔ ");
	else if (i == 1 && j == 15)
		printf("╗");
	else if (i == 15 && j == 1)
		printf("╚ ");
	else if (i == 15 && j == 15)
		printf("╝");
	else if (i == 1 && j != 15 && j != 1)
		printf("┯ ");
	else if (i == 15 && j != 15 && j != 1)
		printf("┷ ");
	else if (j == 1 && i != 15 && i != 1)
		printf("┠ ");
	else if (j == 15 && i != 15 && i != 1)
		printf("┨");
	else
		printf("┼ ");
}

//打印棋盘
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

			if (chessBoard[i][j] == 1) //此处为黑子
				printf("○");
			else if (chessBoard[i][j] == 2) //此处为白子
				printf("●");
			else
			{
				judge(i, j);
			}
		}
		printf("\n");
	}
}

static constexpr int Dx[] = { 1,0,1,1 };						//连子方向
static constexpr int Dy[] = { 0,1,1,-1 };

//完整计算游戏结束时的状态
int gameover()
{
	if (!remainBlank) return draw; //平局
	for (int i = 1; i < GRID_NUM; i++) {
		for (int j = 1; j < GRID_NUM; j++) {
			if (chessBoard[i][j] == blank)
				continue;
			for (int k = 0; k < 4; k++) {
				bool same = 1; int dx = Dx[k], dy = Dy[k];
				for (int v = -2; v <= 2; v++)
					same &= (inboard(i + dx * v, j + dy * v) && chessBoard[i + dx * v][j + dy * v] == chessBoard[i][j]);
				if (same)
					return chessBoard[i][j]; //某一方胜利的计算
			}
		}
	}
	return blank;
}
