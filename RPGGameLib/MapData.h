#ifndef MAPDATA_H
#define MAPDATA_H

#include <map>
#include "Place.h"

#define MAX_MONSTER_PER_PLACE 5

class MapData {
	friend class Place;
public:
	MapData();
	~MapData();
	void ShowDescription(int in_ID);
	string GetExits(int in_ID);
	int NextCity(int cur_city, int next_dir);
	void GenrateMonsters();
	void GenrateMonstersByPlaceId(int id);
	Place *GetPlaceById(int id);

	int  GetRandomMonsterFromCity(int id);
private:
	map<int, Place *> mapdata;
	int num_cities_;
};

#endif