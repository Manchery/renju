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

	agent = getTheIntitative();
	user = agent == black ? white : black;

	if (agent == white) zobrist ^= whiteFirst;

	if (agent == black) {
		//point agentMove = randomMove();
		point agentMove = point(8, 8);
		// agentMove.x += rand() % 3 - 1;
		// agentMove.y += rand() % 3 - 1;
		makeMove(agentMove, agent);
		timeStamp++;
	}

	/*user = white; agent = black;
	makeMove(point(8, 8), user);
	makeMove(point(7, 7), agent);
	makeMove(point(7, 8), user);
	makeMove(point(7, 9), agent);
	makeMove(point(6, 8), user);
	makeMove(point(5, 8), agent);
	makeMove(point(9, 8), user);
	makeMove(point(10, 8), agent);
	makeMove(point(8, 7), user);
	makeMove(point(10, 9), agent);*/

	int eval = 0;
	while (true) {
	    point userMove = getUserMove(eval);
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
		timeStamp++;
		if (gameover(agentMove, agent)) {
			winner = agent; break;
		}
	}

	outputWinner();
	return 0;
}
