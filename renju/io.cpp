#include "io.h"
#include "printchessboard.h"
#include "evaluate.h"
#include <iostream>
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

point getUserMove(int eval)
{
	system("cls");
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << endl; print(); cout << endl;
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
