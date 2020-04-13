#include "gameover.h"

static constexpr int Dx[] = { 1,0,1,1 };						//���ӷ���
static constexpr int Dy[] = { 0,1,1,-1 };

//�����ж��Ƿ���Ϸ������������ pos ��һ����Ӱ�죩������Ӯ����ƽ��
//���� posλ��ȷΪ player���������
int gameover(point pos, int player)
{
	//���� player ���Ƿ�����pos��һ��ʤ��
	for (int k = 0; k < 4; k++) {
		int dx = Dx[k], dy = Dy[k];
		for (int start = -4; start <= 0; start++) {
			bool same = 1;
			for (int v = start; v < start + 5; v++)
				same &= (inboard(pos.x + dx * v, pos.y + dy * v) && chessBoard[pos.x + dx * v][pos.y + dy * v] == chessBoard[pos.x][pos.y]);
			if (same)
				return player;
		}
	}
	// �����Ƿ�ƽ��
	if (!remainBlank) { return draw; } 
	return blank;
}

//����������Ϸ����ʱ��״̬
int gameover()
{
	if (!remainBlank) return draw; //ƽ��
	for (int i = 1; i < GRID_NUM; i++) {
		for (int j = 1; j < GRID_NUM; j++) {
			if (chessBoard[i][j] == blank)
				continue;
			for (int k = 0; k < 4; k++) {
				bool same = 1; int dx = Dx[k], dy = Dy[k];
				for (int v = -2; v <= 2; v++)
					same &= (inboard(i + dx * v, j + dy * v) && chessBoard[i + dx * v][j + dy * v] == chessBoard[i][j]);
				if (same)
					return chessBoard[i][j]; //ĳһ��ʤ���ļ���
			}
		}
	}
	return blank;
}
