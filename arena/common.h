#pragma once

#define blank (0)												//�հ׵�
#define black (1)												//�ڷ�
#define white (2)												//�׷�
#define draw  (3)												//ƽ��
#define opposite(x) (3-(x))										//���֣�black->white, white->black
#define inf (1<<30)												//����������
#define winValue (100000000)									//��ʤ����ĸ�ֵ
#define inboard(a,b) ((a)>0 && (a)<=15 && (b)>0 && (b)<=15)		//���ڼ����з��Ƿ���������
#define GRID_NUM 16												//���̹�ģ	

//��������ĵ��
struct point {
	int x, y;
	point(int x = 0, int y = 0) :x(x), y(y) {}
};
bool operator ==(const point& A, const point& B)
{
	return A.x == B.x && A.y == B.y;
}