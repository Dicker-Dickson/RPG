//MapData is to load map data and connect Place with Cmdparse
//How to use:
//MpData is a global class.
//MapData *CGlobalInfo::map_data = new MapData;
//1. Move to next place.
//int NextPlace = CGlobalInfo::map_data->NextPlace(current_city_, next_direction);
//2. Show description
//CGlobalInfo::map_data->ShowDescription(NextPlace);
//3. Generate monster in place
//CGlobalInfo::map_data->GenrateMonstersInPlace(current_city);
//4. Get battle monster
//int monster_id = CGlobalInfo::map_data->GetBattleMonsters(current_city);

#ifndef MAPDATA_H
#define MAPDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cassert>
#include <map>
#include "monster_data.h"
#include "global_info.h"
#include "place.h"

#include "monster.h"

#define MAX_MONSTER_PER_PLACE 5

using namespace std;

class MapData {
	friend class Place;
public:
	MapData();
	~MapData();

	/// <summary> Show place description </summary>
	/// <param name="place_id"> int type, input: place id </param>
	/// <returns>void type</returns>
	void ShowDescription(int place_id);

	/// <summary> Show place exits </summary>
	/// <param name="place_id"> int type, input: place id </param>
	/// <returns>string type, return is exits</returns>
	string GetExits(int place_id);

	/// <summary> Move to next place </summary>
	/// <param name="current_place_id"> int type, input: current place id </param>
	/// <param name="next_direction"> int type, input: next direction </param>
	/// <returns>int type, return place id, 0 is false.</returns>
	int NextPlace(int current_place_id, int next_direction);

	/// <summary> Generate monsters by map id </summary>
	/// <param name="place_id"> int type, input: place id </param>
	/// <returns>void type</returns>
	void GenrateMonstersInPlace(int place_id);

	/// <summary> Get random monster by place id</summary>
	/// <param name="place_id"> int type, input: place id </param>
	/// <returns>int type, return monster id, return 0 is false</returns>
	int  GetBattleMonsters(int place_id);
private:
	map<int, Place *> map_data_;
	int number_cities_;
};

#endif