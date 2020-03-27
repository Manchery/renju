#include "define.h"
#include "createmoves.h"
#include "makemove.h"
#include "evaluate.h"
#include "printchessboard.h"
#include "searchmove.h"
int searchMove() //ËÑË÷º¯ÊýÖ÷Ìå
{

	return 0;
}

point randomMove() {
	while (true) {
		int x = rand() % (GRID_NUM - 1) + 1;
		int y = rand() % (GRID_NUM - 1) + 1;
		if (chessBoard[x][y] == blank) return point(x, y);
	}
}
