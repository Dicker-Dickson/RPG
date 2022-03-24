#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cassert>
#include "MapData.h"
#include "MonsterData.h"
#include "GlobalInfo.h"

using namespace std;

MapData::MapData() {
	ifstream fin("mapdata.txt");
	if (!fin) {
		cout << "讀檔失敗: mapdata.txt" << endl;
		system("Pause");
		return;
	}
	fin >> num_cities_;
	int id, num_exits, dirs, place_id;
	map<int, Place *>::iterator it;
	string map_name;
	Place *tmp_place;
	for (int i = 0; i < num_cities_; i++) {
		fin >> id >> map_name;
		tmp_place = new Place(map_name);
		it = mapdata.find(id);
		if (it == mapdata.end()) {
			mapdata.insert(pair<int, Place *>(id, tmp_place));
			fin >> num_exits;
			for (int j = 0; j < num_exits; j++) {
				fin >> dirs >> place_id;
				tmp_place->exits[dirs] = place_id;
			}
		}
		else {
			cout << map_name << " with " << id << " has been added before" << endl;
			exit(0);
		}
	}
	fin.close();
#if 0
	for (it = mapdata.begin(); it != mapdata.end(); it++) {
		cout << (*it).first << " " << (*it).second->GetName() << endl;
	}
#endif
}

MapData::~MapData() {
	for (map<int, Place *>::iterator it = mapdata.begin(); it != mapdata.end(); it++) {
		delete it->second;
	}
}

string MapData::GetExits(int in_ID) {
	map<int, Place *>::iterator it = mapdata.find(in_ID);
	if (it == mapdata.end()) {
		cerr << "MapData::GetExits Error";
		exit(0);
	}
	return (*it).second->GetExits();
}

void MapData::ShowDescription(int in_ID) {
	map<int, Place *>::iterator it = mapdata.find(in_ID);
	if (it == mapdata.end()) {
		cerr << "MapData::ShowDescription Error";
		exit(0);
	}
	Place *place = (*it).second;
	assert(place);
	cout << place->GetName() << endl << place->getdescription() << endl;
	cout << place->GetExits() << endl;
}

int MapData::NextCity(int cur_city, int next_dir) {
	map<int, Place *>::iterator it = mapdata.find(cur_city);
	if (it == mapdata.end()) {
		cerr << "user is in a wrong city";
		exit(0);
	}
	assert(next_dir >= 0 && next_dir <= 7);
	return (it->second->exits[next_dir]);
}

void MapData::GenrateMonsters() {
	map<int, Place *>::iterator it;
	int num, monster_id;
	for (it = mapdata.begin(); it != mapdata.end(); it++) {
		num = rand() % MAX_MONSTER_PER_PLACE;
		cout << it->second->name << "產生 " << num << " 隻怪獸" << endl;
		for (int i = 0; i < num; i++) {
			monster_id = CGlobalInfo::monster_data->RandGetMonsterId();
			it->second->gen_monster_by_id(monster_id);
		}
	}
}

void MapData::GenrateMonstersByPlaceId(int id)
{
	int num, monster_id;
	mapdata[id]->monsters.clear();
	num = rand() % MAX_MONSTER_PER_PLACE;
	cout << mapdata[id]->name << "產生 " << num << " 隻怪獸" << endl;
	for (int i = 0; i < num; i++) {
		monster_id = CGlobalInfo::monster_data->RandGetMonsterId();
		mapdata[id]->gen_monster_by_id(monster_id);
	}
}

Place *MapData::GetPlaceById(int id) {
	map<int, Place *>::iterator it = mapdata.find(id);
	if (it == mapdata.end()) {
		cerr << id << " id is wrong";
		exit(0);
	}
	return (it->second);
}

int  MapData::GetRandomMonsterFromCity(int id)
{
	int total_monster = mapdata[id]->monsters.size();

	if (total_monster == 0)
	{
		return -1;
	}
	else {
		auto temp = rand() % total_monster;
		return mapdata[id]->monsters[temp]->GetMonsterId();
	}
}