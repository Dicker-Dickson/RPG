//place is to load place data and build new monsters into place.
//How to use:
//1.Import place document
//string place_name;
//Place* place = new Place(place_name);
//2. Get place name
//auto place_name = place->GetName();
//3. GetDescription
//auto place_description = place->GetDescription();
//4. GetExits
//place->GetExits();
//5. Generate monster by place id
//place->GenerateMonsterByCityId(0);
//6. Show Monsters
//place->ShowMonsters();

// type of exits
// 0: NORTH
// 1: EAST_NORTH
// 2: EAST
// 3: EAST_SOUTH
// 4: SOUTH
// 5: WEST_SOUTH
// 6: WEST
// 7: WEST_NORTH

#ifndef PLACE_H
#define PLACE_H

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include "monster.h"
#include "monster_data.h"
#include "global_info.h"

using namespace std;

#define MAX_DIRECTIONS 8

class Monster;

enum {
	NORTH = 0,
	EAST_NORTH,
	EAST,
	EAST_SOUTH,
	SOUTH,
	WEST_SOUTH,
	WEST,
	WEST_NORTH
};

class Place {
	friend class MapData;
public:
	Place(string filename);
	~Place();

	/// <summary> Get place name </summary>
	/// <returns> string type, return is place name</returns>
	string GetName();

	/// <summary> Get place description </summary>
	/// <returns> string type, return is place description</returns>
	string GetDescription();

	/// <summary> Get exits</summary>
	/// <returns> string type, return is exits</returns>
	string GetExits();

	/// <summary> Generate Monster by place id </summary>
	/// <param name="place_id"> int type, input: place id </param>
	/// <returns>void type</returns>
	void GenerateMonsterByCityId(int place_id);

private:
	string name_;
	string description_;
	int exits_[8];  //store next direction place ID
	vector <Monster *> monsters_;
};

#endif