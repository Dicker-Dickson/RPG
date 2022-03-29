#ifndef GLOBALINFO_H
#define GLOBALINFO_H
#include <string>

class ItemData;
class MapData;
class CmdParser;
class User;
class MonsterData;
class AdventurerData;
class Store;
class WireHouse;
class SkillData;

class CGlobalInfo {
public:
	static ItemData *itm_data;
	static MapData *map_data;
	static CmdParser *parser;
	static User *user;
	static MonsterData *monster_data;
	static AdventurerData* adventurer_data;
	static Store *store;
	static WireHouse* wire_house;
	static SkillData* skill_data;
};

#endif