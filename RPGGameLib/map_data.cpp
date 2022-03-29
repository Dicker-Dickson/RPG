#include "map_data.h"

MapData::MapData() {
	ifstream fin("mapdata.txt");
	if (!fin) {
		cout << "ÅªÀÉ¥¢±Ñ: mapdata.txt" << endl;
		system("Pause");
		return;
	}
	fin >> number_cities_;
	int id, num_exits, dirs, place_id;
	map<int, Place *>::iterator it;
	string map_name;
	Place *tmp_place;
	for (int i = 0; i < number_cities_; i++) {
		fin >> id >> map_name;
		tmp_place = new Place(map_name);
		it = map_data_.find(id);
		if (it == map_data_.end()) {
			map_data_.insert(pair<int, Place *>(id, tmp_place));
			fin >> num_exits;
			for (int j = 0; j < num_exits; j++) {
				fin >> dirs >> place_id;
				tmp_place->exits_[dirs] = place_id;
			}
		}
		else {
			cout << map_name << " with " << id << " has been added before" << endl;
			exit(0);
		}
	}
	fin.close();
}

MapData::~MapData() {
	for (map<int, Place *>::iterator it = map_data_.begin(); it != map_data_.end(); it++) {
		delete it->second;
	}
}

string MapData::GetExits(int place_id) {
	map<int, Place *>::iterator it = map_data_.find(place_id);
	if (it == map_data_.end()) {
		cerr << "MapData::GetExits Error";
		exit(0);
	}
	return (*it).second->GetExits();
}

void MapData::ShowDescription(int place_id) {
	map<int, Place *>::iterator it = map_data_.find(place_id);
	if (it == map_data_.end()) {
		cerr << "MapData::ShowDescription Error";
		exit(0);
	}
	Place *place = (*it).second;
	assert(place);
	cout << place->GetName() << endl << place->GetDescription() << endl;
	cout << place->GetExits() << endl;
}

int MapData::NextPlace(int current_place_id, int next_direction) {
	map<int, Place *>::iterator it = map_data_.find(current_place_id);
	if (it == map_data_.end()) {
		cerr << "user is in a wrong place";
		exit(0);
	}
	assert(next_direction >= 0 && next_direction <= 7);
	return (it->second->exits_[next_direction]);
}

void MapData::GenrateMonstersInPlace(int place_id)
{
	int num, monster_id;
	map_data_[place_id]->monsters_.clear();
	num = rand() % MAX_MONSTER_PER_PLACE;
	cout << map_data_[place_id]->name_ << "²£¥Í " << num << " °¦©ÇÃ~" << endl;
	for (int i = 0; i < num; i++) {
		monster_id = CGlobalInfo::monster_data->RandGetMonsterId();
		map_data_[place_id]->GenerateMonsterByCityId(monster_id);
	}
}

int  MapData::GetBattleMonsters(int place_id)
{
	int total_monster = map_data_[place_id]->monsters_.size();

	if (total_monster == 0)
	{
		return 0;
	}
	else {
		auto temp = rand() % total_monster;
		return map_data_[place_id]->monsters_[temp]->GetMonsterId();
	}
}