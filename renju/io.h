#pragma once

#include "define.h"
#include <algorithm>

//�����ʼ��
int getTheIntitative();

//�ȴ��û�����
point getUserMove(int eval, point agentLastMove);

//���Ӯ��
void outputWinner();

//AI����ʱ�ĵȴ�����
void userWaiting();

//�����¼�Խ��и���
bool readRecord();

//�����¼
void writeRecord();

//����
void regret(int& state, point& lastMove);