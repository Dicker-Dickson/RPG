#include <iostream>
#include <fstream>
#include <cassert>
#include "Place.h"
#include "MapData.h"
#include "MonsterData.h"
#include "GlobalInfo.h"

using namespace std;

Place::Place(string filename) {
	ifstream fin(filename);
	if (!fin) {
		cout << "讀檔失敗: " << filename << endl;
		return;
	}
	fin >> name >> description;
	fin.close();
	for (int i = 0; i < MAX_DIRECTIONS; i++) {
		exits[i] = 0;
	}
}

string Place::GetExits() {
	string output;
	int NextCity;
	bool comma = false;
	for (int i = 0; i < MAX_DIRECTIONS; i++) {
		NextCity = exits[i];
		if (NextCity > 0) {
			if (comma)
				output += string("，");
			switch (i) {
			case eNorth:
				output += string("往北方(north)是 ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eEastNorth:
				output += string("往東北方(eastnorth)是 ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eEast:
				output += string("往東方(east)是 ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eEastSouth:
				output += string("往東南方(eastsouth)是 ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eSouth:
				output += string("往南方(south)是 ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eWestSouth:
				output += string("往西南方(westsouth)是 ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eWest:
				output += string("往西方(west)是 ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eWestNorth:
				output += string("往西北方(westnorth)是 ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			default:
				cerr << "Error in calling Place::show_exits" << endl;
				exit(0);
			}
			comma = true;
		}
	}
	if (comma)
		output += string("。");
	return output;
}

void Place::gen_monster_by_id(int id) {
	MonsterType *type = CGlobalInfo::monster_data->GetMonstertypeById(id);
	assert(type);
	Monster *tmp = new Monster(type);
	monsters.push_back(tmp);
}

Monster *Place::get_monster_by_engname(string engname) {
	for (vector <Monster *>::iterator it = monsters.begin(); it != monsters.end(); it++) {
		if ((*it)->GetEngname() == engname)
			return (*it);
	}
	return NULL;
}

bool Place::remove_moster_by_engname(string engname) {
	for (vector <Monster *>::iterator it = monsters.begin(); it != monsters.end(); it++) {
		if ((*it)->GetEngname() == engname) {
			delete (*it);
			monsters.erase(it);
			return true;
		}
	}
	return false;
}

void Place::show_mosters() {
	vector <Monster *>::iterator it = monsters.begin();
	if (it == monsters.end()) {
		cout << "無任何怪物資料" << endl;
		return;
	}
	for (; it != monsters.end(); it++) {
		cout << (*it)->GetBasicData() << endl;
	}
}