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

//�ַ�������
void Trim(string & str)
{
	string blanks("\f\v\r\t\n ");
	str.erase(0, str.find_first_not_of(blanks));
	str.erase(str.find_last_not_of(blanks) + 1);
}

//ѯ������
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

enum stateSet {NORMAL, INVALID, REGRET_SUCCESS, REGRET_FAILED}; //����ĺϷ�����֤

const string stateIndicator[4] = {								//��ʾ��Ϣ
	"������ָ�",
	"ָ���������������룺",
	"����ɹ�����������壺",
	"������Ҫ���壬����������ָ�"
};

//�ȴ��û�����
point getUserMove(int eval, point agentLastMove)
{
	static int state = NORMAL;
	point lastMove = agentLastMove;
	while (true) {
		system("cls");
		cout << "*************�������˻�����AI*************" << endl;
		cout << endl; print(); cout << endl;
		if (!(lastMove == point()))
			cout << "�����ϲ����ӣ�(" << lastMove.x << "," << lastMove.y << ")" << endl;
		if (lastMove == agentLastMove)
			cout << (agent == black ? "��" : "��") << "���������: " << ((eval > 0) ? "+" : "") << eval << endl << endl;
		else
			cout << "����������ǰ�����ã���ȵ������ٴ�����" << endl << endl;
		cout << "����: move r c  ��ʾ���ӵ㣨r,c �ֱ��ʾ���У�" << endl;
		cout << "����: regret ������" << endl << endl;
		cout << stateIndicator[state];
		string input;
		getline(cin, input);
		istringstream sin(input);
		bool fail = false;
		string order; sin >> order;
		if (order == "regret")
		{
			regret(state, lastMove);
			continue;
		}
		if (order != "move") fail = true;
		if (!fail) {
			int x=-1, y=-1;
			sin >> x >> y;
			if (!inboard(x, y) || chessBoard[x][y]!=blank)
				fail = true;
			else
				return point(x, y);
		}
		state = INVALID;
	}
}

//���Ӯ��
void outputWinner()
{
	system("cls");
	cout << "*************�������˻�����AI*************" << endl;
	cout << endl; print(); cout << endl;
	if (winner == draw) { cout << "ƽ�֣�" << endl; return; }
	if (winner == agent) cout << "����"; else cout << "�û�";
	if (winner == black) cout << "ִ��"; else cout << "ִ��";
	cout << "��ʤ��" << endl;
}

//AI����ʱ�ĵȴ�����
void userWaiting()
{
	system("cls");
	cout << "*************�������˻�����AI*************" << endl;
	cout << endl; print(); cout << endl;
	cout << "����˼����..." << endl;
}

//�����¼�Խ��и���
bool readRecord()
{
	ifstream fin(".\\record.txt");
	fin >> agent;
	if (agent != black && agent != white) return false;
	
	cout << "��⵽���ף��Ƿ���룿[Y/N]";
	string input;
	getline(cin, input); Trim(input);
	char ch = 'N';
	if (input.length() > 0) ch = input[0];
	if (!(ch == 'Y' || ch == 'y')) return false;

	int x, y, cur = black;
	if (agent == white) zobrist ^= MinFirstValue;
	while (!fin.eof() && fin.good())
	{
		fin >> x >> y;
		if (makeMove(point(x, y), cur))
		{
			cur = opposite(cur);
			timeStamp++;
		}
	}

	return true;
}

//�����¼
void writeRecord()
{
	ofstream fout(".\\record.txt");
	if (!fout.is_open()) { return; }
	fout << agent << endl;
	for (auto it : moveRecord)
	{
		fout << it.x << " " << it.y << endl;
	}
}

//����
void regret(int& state, point& lastMove)
{
	if (moveRecord.size() >= 2U)
	{
		unMakeMove(agent);
		unMakeMove(user);
		lastMove = (moveRecord.empty() ? point() : moveRecord.back());
		state = REGRET_SUCCESS;
	}
	else
	{
		state = REGRET_FAILED;
	}
}
