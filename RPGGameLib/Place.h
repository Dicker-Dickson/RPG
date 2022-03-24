#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include "Monster.h"
using namespace std;

#define MAX_DIRECTIONS 8
enum {
	eNorth = 0,
	eEastNorth,
	eEast,
	eEastSouth,
	eSouth,
	eWestSouth,
	eWest,
	eWestNorth
};
// type of exits
// 0: north
// 1: eastnorth
// 2: east
// 3: eastsouth
// 4: south
// 5: westsouth
// 6: west
// 7: westnorth

class Monster;

class Place {
	friend class MapData;
public:
	Place(string filename);
	string GetName() { return name; };
	string getdescription() { return description; };
	string GetExits();
	void gen_monster_by_id(int);
	void show_mosters();
	Monster *get_monster_by_engname(string);
	bool remove_moster_by_engname(string);
private:
	string name;
	string description;
	int exits[8]; // store next direction place ID
	vector <Monster *> monsters;
};

#endif