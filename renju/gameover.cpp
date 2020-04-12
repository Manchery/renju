#include "gameover.h"

static constexpr int Dx[] = { 1,0,1,1 };						//搜索方向控制
static constexpr int Dy[] = { 0,1,1,-1 };

//快速判断是否游戏结束
bool gameover(point pos, int player)
{
	//计算是否还有合法落子点
	if (!remainBlank) { return true; }

	//计算某一方是否胜利
	for (int k = 0; k < 4; k++) {
		int dx = Dx[k], dy = Dy[k];
		for (int start = -4; start <= 0; start++) {
			bool same = 1;
			for (int v = start; v < start + 5; v++)
				same &= (inboard(pos.x + dx * v, pos.y + dy * v) && chessBoard[pos.x + dx * v][pos.y + dy * v] == chessBoard[pos.x][pos.y]);
			if (same)
				return true;
		}
	}
	return false;
}

//完整计算游戏结束时的状态
int gameover()
{
	bool isDraw = true;
	for (int i = 1; i < GRID_NUM; i++) {
		for (int j = 1; j < GRID_NUM; j++) {
			for (int k = 0; k < 4; k++) {
				if (!chessBoard[i][j]) { //平局计算
					isDraw = false;
					continue; 
				}
				bool same = 1; int dx = Dx[k], dy = Dy[k];
				for (int v = -2; v <= 2; v++)
					same &= (inboard(i + dx * v, j + dy * v) && chessBoard[i + dx * v][j + dy * v] == chessBoard[i][j]);
				if (same)
					return chessBoard[i][j]; //某一方胜利的计算
			}
		}
	}
	return (isDraw? draw : blank);
}
