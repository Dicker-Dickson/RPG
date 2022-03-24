#include <iostream>
#include <fstream>
#include "MonsterData.h"

MonsterType::MonsterType(int in_id, string in_name, string in_eng, int in_hp, int in_sp, int in_rough, int in_level, int in_exp) {
	id = in_id;
	name = in_name;
	prefix_eng_name = in_eng;
	max_hp = in_hp;
	max_sp = in_sp;
	max_rough = in_rough;
	level = in_level;
	exp = in_exp;
}

MonsterData::MonsterData() {
	ifstream fin("monsterdata.txt");
	if (!fin) {
		cout << "Ū�ɥ���: monsterdata.txt" << endl;
		exit(0);
	}
	int tmp_id;
	string tmp_name;
	string tmp_eng;
	int tmp_hp, tmp_sp, tmp_rough, tmp_level, tmp_exp;
	MonsterType *tmp_type;
	while (fin >> tmp_id >> tmp_name >> tmp_eng >> tmp_hp >> tmp_sp >> tmp_rough >> tmp_level >> tmp_exp) {
		tmp_type = new MonsterType(tmp_id, tmp_name, tmp_eng, tmp_hp, tmp_sp, tmp_rough, tmp_level, tmp_exp);
		monsterdata.push_back(tmp_type);
	}
#if 0
	for (vector<MonsterType *>::iterator it = monsterdata.begin(); it != monsterdata.end(); it++) {
		cout << (*it)->id << " " << (*it)->name << " " << (*it)->prefix_eng_name_ << " " << (*it)->max_hp << " " << (*it)->max_sp << " " << (*it)->max_rough << endl;
	}
#endif
	fin.close();
}

MonsterData::~MonsterData() {
	for (vector<MonsterType *>::iterator it = monsterdata.begin(); it != monsterdata.end(); it++) {
		delete (*it);
	}
}

int MonsterData::RandGetMonsterId() {
	int idx = rand() % monsterdata.size();
	return monsterdata[idx]->id;
}

MonsterType *MonsterData::GetMonstertypeById(int id) {
	for (vector<MonsterType *>::iterator it = monsterdata.begin(); it != monsterdata.end(); it++) {
		if ((*it)->id == id) {
			return (*it);
		}
	}
	return NULL;
}

int MonsterData::GetHP()
{
	return monsterdata[0]->max_hp;
}

int MonsterData::GetSP()
{
	return monsterdata[0]->max_sp;
}

int MonsterData::GetRough()
{
	return monsterdata[0]->max_rough;
}

int MonsterData::GetLevel()
{
	return monsterdata[0]->level;
}

int MonsterData::GetExp()
{
	return monsterdata[0]->exp;
}