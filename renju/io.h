#pragma once

#include "define.h"
#include <algorithm>

int getTheIntitative();

point getUserMove(int eval, point agentLastMove);

void outputWinner();

void userWaiting();

bool readRecord();

void writeRecord();