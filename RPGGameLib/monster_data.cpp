#include <iostream>
#include <fstream>
#include "monster_data.h"

MonsterType::MonsterType(int in_id, string in_name, int in_hp, int in_sp, int in_rough, int in_level, int in_exp) {
	id = in_id;
	name = in_name;

	max_hp = in_hp;
	max_sp = in_sp;
	max_rough = in_rough;
	level = in_level;
	exp = in_exp;
}

MonsterData::MonsterData() {
	ifstream fin("monsterdata.txt");
	if (!fin) {
		cout << "ÅªÀÉ¥¢±Ñ: monsterdata.txt" << endl;
		exit(0);
	}
	int tmp_id;
	string tmp_name;
	int tmp_hp, tmp_sp, tmp_rough, tmp_level, tmp_exp;
	MonsterType *tmp_type;
	while (fin >> tmp_id >> tmp_name >> tmp_hp >> tmp_sp >> tmp_rough >> tmp_level >> tmp_exp) {
		tmp_type = new MonsterType(tmp_id, tmp_name, tmp_hp, tmp_sp, tmp_rough, tmp_level, tmp_exp);
		monster_data_.push_back(tmp_type);
	}

	fin.close();
}

MonsterData::~MonsterData() {
	for (vector<MonsterType *>::iterator it = monster_data_.begin(); it != monster_data_.end(); it++) {
		delete (*it);
	}
}

int MonsterData::RandGetMonsterId() {
	int idx = rand() % monster_data_.size();
	return monster_data_[idx]->id;
}

MonsterType *MonsterData::GetMonstertypeById(int id) {
	for (vector<MonsterType *>::iterator it = monster_data_.begin(); it != monster_data_.end(); it++) {
		if ((*it)->id == id) {
			return (*it);
		}
	}
	return NULL;
}