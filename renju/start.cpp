#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "gameover.h"
#include "io.h"
#include "hash.h"
int main()
{
	//哈希表初始化
	initHashValue();

	//读入记录
	if (!readRecord())
		agent = getTheIntitative();
	user = agent == black ? white : black;
	point agentLastMove(0, 0);

	//终局判定
	if (winner = gameover())
	{
		outputWinner();
		writeRecord();
		system("pause");
		return 0;
	}
	int eval = 0;

	//AI计算第一步棋
	if (!getRecord)
	{
		if (agent == white) zobrist ^= whiteFirst;
		if (agent == black) {
			userWaiting();
			std::pair<point, int> searchResult = searchMove();
			point agentMove = searchResult.first;
			eval = searchResult.second;
			makeMove(agentMove, agent);
			agentLastMove = agentMove;
			timeStamp++;
			if (gameover(agentMove, agent)) {
				winner = agent;
			}
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

	//AI和玩家轮流操作
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

	//判定终局时的游戏状态
	//并保存相关信息
	winner = (gameover() == draw ? draw : winner);
	outputWinner();
	writeRecord();
	system("pause");
	return 0;
}
