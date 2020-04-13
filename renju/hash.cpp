#include "hash.h"

hash_t zobristValue[GRID_NUM][GRID_NUM][3];						//ÿ��λ�õ�ÿ�����ӵ�zobristֵ
hash_t whiteFirstValue, MinFirstValue;							//��ǰ�������к�������е�zobristֵ
hash_t zobrist;													//��ǰ����zobristֵ������˭���֣�������min����max

std::unordered_map<hash_t, hashNode> hashMap;					//��ϣ��

//�����������
hash_t rand64() {
	return rand() ^ ((hash_t)rand() << 15) ^ ((hash_t)rand() << 30) ^ ((hash_t)rand() << 45) ^ ((hash_t)rand() << 60);
}

//zobristֵ�ĳ�ʼ��
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

//������δ�����ʵĹ�ϣ�ڵ�
void hashMapClean()
{
	for (auto iter = hashMap.begin(); iter != hashMap.end();) {
		if (timeStamp - iter->second.time > HASH_CLEAN_TIME)
			iter = hashMap.erase(iter);
		else
			iter++;
	}
}
