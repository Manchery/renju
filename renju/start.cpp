#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "gameover.h"
#include "io.h"
int main()
{
	agent = getTheIntitative();
	user = agent == black ? white : black;

	if (agent == black) {
		//point agentMove = randomMove();
		point agentMove = point(8, 8);
		makeMove(agentMove, agent);
	}
	while (true) {
	    point userMove = getUserMove();
		makeMove(userMove, user);
		if (gameover(userMove, user)) {
			winner = user; break;
		}
		userWaiting();
		point agentMove = searchMove();
		makeMove(agentMove, agent);
		if (gameover(agentMove, agent)) {
			winner = agent; break;
		}
	}

	outputWinner();
	return 0;
}
