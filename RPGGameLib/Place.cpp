#include "place.h"
#include "map_data.h"
using namespace std;

Place::Place(string filename) {
	ifstream fin(filename);
	if (!fin) {
		cout << "讀檔失敗: " << filename << endl;
		return;
	}
	fin >> name_ >> description_;
	fin.close();
	for (int i = 0; i < MAX_DIRECTIONS; i++) {
		exits_[i] = 0;
	}
}

Place::~Place()
{
}

string Place::GetName()
{
	return name_;
}

string Place::GetDescription()
{
	return description_;
}

string Place::GetExits() {
	string output;
	int NextPlace;
	bool comma = false;
	for (int i = 0; i < MAX_DIRECTIONS; i++) {
		NextPlace = exits_[i];
		if (NextPlace > 0) {
			if (comma)
				output += string("，");
			switch (i) {
			case NORTH:
				output += string("往北方(north)是 ") + CGlobalInfo::map_data->map_data_[NextPlace]->GetName();
				break;
			case EAST_NORTH:
				output += string("往東北方(eastnorth)是 ") + CGlobalInfo::map_data->map_data_[NextPlace]->GetName();
				break;
			case EAST:
				output += string("往東方(east)是 ") + CGlobalInfo::map_data->map_data_[NextPlace]->GetName();
				break;
			case EAST_SOUTH:
				output += string("往東南方(eastsouth)是 ") + CGlobalInfo::map_data->map_data_[NextPlace]->GetName();
				break;
			case SOUTH:
				output += string("往南方(south)是 ") + CGlobalInfo::map_data->map_data_[NextPlace]->GetName();
				break;
			case WEST_SOUTH:
				output += string("往西南方(westsouth)是 ") + CGlobalInfo::map_data->map_data_[NextPlace]->GetName();
				break;
			case WEST:
				output += string("往西方(west)是 ") + CGlobalInfo::map_data->map_data_[NextPlace]->GetName();
				break;
			case WEST_NORTH:
				output += string("往西北方(westnorth)是 ") + CGlobalInfo::map_data->map_data_[NextPlace]->GetName();
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

void Place::GenerateMonsterByCityId(int place_id) {
	MonsterType *type = CGlobalInfo::monster_data->GetMonstertypeById(place_id);
	assert(type);
	Monster *tmp = new Monster(type);
	monsters_.push_back(tmp);
}