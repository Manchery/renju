#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "gameover.h"
#include "io.h"
#include "hash.h"

int main()
{
	//��ϣ��ʼ��
	initHashValue();

	//�����¼
	if (!readRecord()) {
		agent = getTheIntitative(); // ѯ������
		if (agent == white) zobrist ^= MinFirstValue;
	}
	user = agent == black ? white : black;

	//�վ��ж�
	if (winner = gameover())
	{
		outputWinner();
		writeRecord();
		system("pause");
		return 0;
	}
	point agentLastMove(0, 0);
	int eval = 0;

	//AI�����һ����
	if ((agent == black && moveRecord.size() % 2 == 0) || 
		(agent == white && moveRecord.size() % 2 == 1))
	{
		userWaiting();
		std::pair<point, int> searchResult = searchMove();
		point agentMove = searchResult.first;
		eval = searchResult.second;
		makeMove(agentMove, agent);
		agentLastMove = agentMove;
		timeStamp++;
		winner = gameover(agentMove, agent);
	}

	//AI�������������
	while (!winner) {
	    point userMove = getUserMove(eval, agentLastMove);
		makeMove(userMove, user);
		timeStamp++;
		if (winner = gameover(userMove, user))
			break;
		userWaiting();
		std::pair<point, int> searchResult = searchMove();
		point agentMove = searchResult.first;
		eval = searchResult.second;
		makeMove(agentMove, agent);
		agentLastMove = agentMove;
		timeStamp++;
		if (winner = gameover(agentMove, agent))
			break;
		writeRecord();
	}

	//�ж��վ�ʱ����Ϸ״̬
	//�����������Ϣ
	outputWinner();
	writeRecord();
	system("pause");
	return 0;
}
