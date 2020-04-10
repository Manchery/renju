#include "io.h"
#include "hash.h"
#include "printchessboard.h"
#include "evaluate.h"
#include "makemove.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void Trim(string & str)
{
	string blanks("\f\v\r\t\n ");
	str.erase(0, str.find_first_not_of(blanks));
	str.erase(str.find_last_not_of(blanks) + 1);
}

int getTheIntitative() {
	system("cls");
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << endl; print(); cout << endl;
	cout << "输入: newblack  电脑先手" << endl;
	cout << "输入: newwhite  电脑后手" << endl << endl;

	while (true) {
		string input;
		getline(cin, input); Trim(input);
		if (input == "newblack") return black;
		else if (input == "newwhite") return white;
		else {
			cout << endl << "请重新输入！" << endl;
			cout << "输入: newblack  电脑先手" << endl;
			cout << "输入: newwhite  电脑后手" << endl << endl;
		}
	}
}

point getUserMove(int eval, point agentLastMove)
{
	system("cls");
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << endl; print(); cout << endl;
	if (!(agentLastMove == point()))
		cout << "电脑上步落子：(" << agentLastMove.x << "," << agentLastMove.y << ")" << endl;
	cout << (agent == black ? "黑" : "白") << "棋局面评估: " << ((eval > 0) ? "+" : "") << eval << endl << endl;
	cout << "输入: move r c  表示落子点（r,c 分别表示行列）" << endl << endl;

	while (true) {
		string input;
		getline(cin, input); //Trim(input);
		istringstream sin(input);
		bool fail = false;
		string order; sin >> order; if (order != "move") fail = true;
		if (!fail) {
			int x=-1, y=-1;
			sin >> x >> y;
			if (!inboard(x, y) || chessBoard[x][y]!=blank)
				fail = true;
			else
				return point(x, y);
		}
		cout << endl << "请重新输入！" << endl;
		cout << "输入: move r c  表示落子点（r,c 分别表示行列）" << endl << endl;
	}
}

void outputWinner()
{
	system("cls");
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << endl; print(); cout << endl;
	if (winner == agent) cout << "电脑"; else cout << "用户";
	if (winner == black) cout << "执黑"; else cout << "执白";
	cout << "获胜。" << endl;
}

void userWaiting()
{
	system("cls");
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << endl; print(); cout << endl;
	cout << "电脑思考中..." << endl;
}

bool readRecord()
{
	ifstream fin(".\\record.txt");
	fin >> agent;
	if (!agent) return false;
	if (agent)
	{
		cout << "检测到棋谱，是否读入？[Y/N]";// << endl;
		string input;
		getline(cin, input); Trim(input);
		char ch = 'N';
		if (input.length() > 0) ch = input[0];
		if (!(ch == 'Y' || ch == 'y'))
		{
			return false;
		}
	}

	if (agent == white) zobrist ^= whiteFirst;

	int x, y, cur = black;
	while (!fin.eof() && fin.good())
	{
		fin >> x >> y;
		if (makeMove(point(x, y), cur))
		{
			cur = opposite(cur);
			getRecord++;
			timeStamp++;
		}
	}

	return true;
}

void writeRecord()
{
	ofstream fout(".\\record.txt");
	if (!fout.is_open()) { 
#ifdef DBG_LOG
		cout << "棋谱文件不能正常读写." << endl;
#endif // DBG_LOG
		return; }
	fout << agent << endl;
	for (auto it : moveRecord)
	{
		fout << it.x << " " << it.y << endl;
	}
}
