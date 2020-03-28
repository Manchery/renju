#include "hash.h"

hash_t zobristValue[GRID_NUM][GRID_NUM][3];
hash_t whiteFirstValue, MinFirstValue;
hash_t zobrist; // 当前局面hash值，包括谁先手，先手是min还是max

hash_t rand64() {
	return rand() ^ ((hash_t)rand() << 15) ^ ((hash_t)rand() << 30) ^ ((hash_t)rand() << 45) ^ ((hash_t)rand() << 60);
}

void initHashValue() {
	for (int i = 1; i < GRID_NUM; i++)
		for (int j = 1; j < GRID_NUM; j++) {
			zobristValue[i][j][1] = rand64();
			zobristValue[i][j][2] = rand64();
		}
	whiteFirstValue = rand64();
	MinFirstValue = rand64();

	zobrist = 0;
	hashMap.clear();
}

std::unordered_map<hash_t, hashNode> hashMap;
int hashSuccess;
