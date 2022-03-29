//MonsterData is to load monster data and save monster data into MonsterType
//How to use:
//MonsterData is a global object. It be initialed at first.
//1. Get random monster id
//CGlobalInfo::monster_data->RandGetMonsterId();
//2. Get monster by id
//CGlobalInfo::monster_data->RandGetMonsterId(0);

#ifndef MONSTERDATA_H
#define MONSTERDATA_H

#include <string>
#include <vector>

using namespace std;

class MonsterType {
	friend class MonsterData;
	friend class Monster;
public:
	MonsterType(int in_id, string in_name, int in_hp, int in_sp, int in_rough, int in_level, int in_exp);
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

	/// <summary> Get random monster id </summary>
	/// <returns>int type, return is random monster id</returns>
	int RandGetMonsterId();

	/// <summary> Generate Monster by id </summary>
	/// <param name="id"> int type, input: monster id </param>
	/// <returns>MonsterType* type, return is MonsterType</returns>
	MonsterType *GetMonstertypeById(int id);

private:
	vector<MonsterType *> monster_data_;
};

#endif