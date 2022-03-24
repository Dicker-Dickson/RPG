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
		cout << "Ū�ɥ���: " << filename << endl;
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
				output += string("�A");
			switch (i) {
			case eNorth:
				output += string("���_��(north)�O ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eEastNorth:
				output += string("���F�_��(eastnorth)�O ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eEast:
				output += string("���F��(east)�O ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eEastSouth:
				output += string("���F�n��(eastsouth)�O ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eSouth:
				output += string("���n��(south)�O ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eWestSouth:
				output += string("����n��(westsouth)�O ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eWest:
				output += string("�����(west)�O ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			case eWestNorth:
				output += string("����_��(westnorth)�O ") + CGlobalInfo::map_data->mapdata[NextCity]->GetName();
				break;
			default:
				cerr << "Error in calling Place::show_exits" << endl;
				exit(0);
			}
			comma = true;
		}
	}
	if (comma)
		output += string("�C");
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
		cout << "�L����Ǫ����" << endl;
		return;
	}
	for (; it != monsters.end(); it++) {
		cout << (*it)->GetBasicData() << endl;
	}
}