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

point getUserMove(int eval, point agentLastMove)
{
	system("cls");
	cout << "*************�������˻�����AI*************" << endl;
	cout << endl; print(); cout << endl;
	if (!(agentLastMove == point()))
		cout << "�����ϲ����ӣ�(" << agentLastMove.x << "," << agentLastMove.y << ")" << endl;
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

bool readRecord()
{
	ifstream fin(".\\record.txt");
	fin >> agent;
	if (!agent) return false;
	if (agent)
	{
		cout << "��⵽���ף��Ƿ���룿[Y/N]";// << endl;
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
		cout << "�����ļ�����������д." << endl;
#endif // DBG_LOG
		return; }
	fout << agent << endl;
	for (auto it : moveRecord)
	{
		fout << it.x << " " << it.y << endl;
	}
}
