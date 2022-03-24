#ifndef MONSTERDATA_H
#define MONSTERDATA_H

#include <string>
#include <vector>

using namespace std;

class MonsterType {
	friend class MonsterData;
	friend class Monster;
public:
	MonsterType(int, string, string, int, int, int, int, int);
private:
	int id;
	string name;
	string prefix_eng_name;
	int max_hp;
	int max_sp;
	int max_rough;
	int level;
	int exp;
};

class MonsterData {
public:
	MonsterData();
	~MonsterData();
	int RandGetMonsterId();
	MonsterType *GetMonstertypeById(int);
	int GetHP();
	int GetSP();
	int GetRough();
	int GetLevel();
	int GetExp();

private:
	vector<MonsterType *> monsterdata;
};

#endif