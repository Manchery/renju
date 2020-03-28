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
	cout << "*************�������˻�����AI*************" << endl;
	cout << endl; print(); cout << endl;
	cout << "����: newblack  ��������" << endl;
	cout << "����: newwhite  ���Ժ���" << endl << endl;
	
	while (true) {
		string input;
		getline(cin, input); Trim(input);
		if (input == "newblack") return black;
		else if (input == "newwhite") return white;
		else {
			cout << endl << "���������룡" << endl;
			cout << "����: newblack  ��������" << endl;
			cout << "����: newwhite  ���Ժ���" << endl << endl;
		}
	}
}

point getUserMove(int eval)
{
	system("cls");
	cout << "*************�������˻�����AI*************" << endl;
	cout << endl; print(); cout << endl;
	cout << (agent == black ? "��" : "��") << "���������: " << ((eval > 0) ? "+" : "") << eval << endl << endl;
	cout << "����: move r c  ��ʾ���ӵ㣨r,c �ֱ��ʾ���У�" << endl << endl;

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
		cout << endl << "���������룡" << endl;
		cout << "����: move r c  ��ʾ���ӵ㣨r,c �ֱ��ʾ���У�" << endl << endl;
	}
}

void outputWinner()
{
	system("cls");
	cout << "*************�������˻�����AI*************" << endl;
	cout << endl; print(); cout << endl;
	if (winner == agent) cout << "����"; else cout << "�û�";
	if (winner == black) cout << "ִ��"; else cout << "ִ��";
	cout << "��ʤ��" << endl;
}

void userWaiting()
{
	system("cls");
	cout << "*************�������˻�����AI*************" << endl;
	cout << endl; print(); cout << endl;
	cout << "����˼����..." << endl;
}
