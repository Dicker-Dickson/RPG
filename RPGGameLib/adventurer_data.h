#ifndef ADVENTURER_DATA_H
#define ADVENTURER_DATA_H

#include <string>
#include <vector>
#include "GlobalInfo.h"
#include <sstream>
#include "skill_data.h"
#include "skill.h"

using namespace std;

class Item;
class Food;
class Weapon;
class Bag;

struct AdventurerAttribute {
	int id;
	string name;
	string career;
	int max_hp;
	int max_mp;
	int max_sp;
	int max_rough;
	int level;
	int exp;
	int ability_points;
	int skill_points;

	int defense;
	int dexterity;
	int strength;
	int intelligence;
	int lucky;

	int money;
};

class AdventurerData {
public:

	AdventurerData();
	~AdventurerData();

	AdventurerAttribute GetAdventurerData(int id);
	void Save(AdventurerAttribute attribute);
	bool NewData();
	void ReadData(string user);
	void SetUserName(string user);
	void DeleteAdventurer(int id);
	void SetCurrentAdventurerId(int id);
	int GetCurrentAdventurerId();
	void PrintAdventurerData();
	void Save();
	void SaveBagFood(vector<Item*>);
	void SaveBagWeapon(vector<Item*>);
	void SaveBagArmor(vector<Item*>);
	void LoadBagFood(string user, string id);
	void LoadBagWeapon(string user, string id);
	void LoadBagArmor(string user, string id);
	vector<Item*> AdventurerData::GetBagItem(int id);
	string GetCurrentAdventurerCareer();
	vector<SkillAttribute> AdventurerData::LoadSkill(string id);
	vector<Item*> AdventurerData::LoadEquipment(string id);
	void SaveEquipment(vector<Item*>);
	void SaveSkill(vector<Skill*>skill);

private:
	vector<AdventurerAttribute> adventurer_data_;
	vector<Item*> item_;
	string user_;
	int current_id_;
	string current_career_;
	vector<SkillAttribute> skill_;
	vector<Item*> equipment_;
};

#endif