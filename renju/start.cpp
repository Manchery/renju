#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "gameover.h"
#include "io.h"
#include "hash.h"
int main()
{
	initHashValue();

	if (!readRecord())
		agent = getTheIntitative();
	user = agent == black ? white : black;

	point agentLastMove(0, 0);

	if (winner = gameover())
	{
		outputWinner();
		writeRecord();
		system("pause");
		return 0;
	}

	if (!getRecord)
	{
		if (agent == white) zobrist ^= whiteFirst;
		if (agent == black) {
			//point agentMove = randomMove();
			point agentMove = point(8, 8);
			// agentMove.x += rand() % 3 - 1;
			// agentMove.y += rand() % 3 - 1;
			makeMove(agentMove, agent);
			agentLastMove = agentMove;
			timeStamp++;
		}
	}
	else if ((agent + getRecord) % 2)
	{
		std::pair<point, int> searchResult = searchMove();
		point agentMove = searchResult.first;
		int eval = searchResult.second;
		makeMove(agentMove, agent);
		agentLastMove = agentMove;
		timeStamp++;
		if (gameover(agentMove, agent)) {
			winner = agent;
		}
	}

	int eval = 0;
	while (!winner) {
	    point userMove = getUserMove(eval, agentLastMove);
		makeMove(userMove, user);
		timeStamp++;
		if (gameover(userMove, user)) {
			winner = user; break;
		}
		userWaiting();
		std::pair<point, int> searchResult = searchMove();
		point agentMove = searchResult.first;
		eval = searchResult.second;
		makeMove(agentMove, agent);
		agentLastMove = agentMove;
		timeStamp++;
		if (gameover(agentMove, agent)) {
			winner = agent; break;
		}
		writeRecord();
	}

	outputWinner();
	writeRecord();
	system("pause");
	return 0;
}
