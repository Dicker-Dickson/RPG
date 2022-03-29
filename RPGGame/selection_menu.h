#ifndef SELECTION_MENU_H
#define SELECTION_MENU_H

#include "global_info.h"
#include "adventurer_data.h"
#include <iostream>
#include "item_data.h"
#include <ctime>
#include "map_data.h"
#include "cmd_parser.h"
#include "beginner.h"
#include "warrior.h"
#include "thief.h"
#include "magician.h"
#include "archer.h"
#include "adventurer_factory.h"
#include "adventurer_data.h"
#include "battle_scene.h"
#include "user.h"
#include "store.h"
#include "wirehouse.h"
#include "skill_data.h"

#include <map>

using namespace std;

class SelectionMenu {
public:
	SelectionMenu();
	~SelectionMenu();
	void ShowSelectionMenu();

private:
	void ShowMap();
	void ShowAttribute();
	void ShowAddAbility();
	void ShowLearnSkill();
	void ShowStore();
	void ShowBuyMenu();
	void ShowBuyFoodMenu();
	void ShowBuyWeaponMenu();
	void ShowBuyArmorMenu();
	void ShowSellMenu();
	void ShowSellFoodMenu();
	void ShowSellWeaponMenu();
	void ShowSellArmorMenu();
	void ShowLevelUpMenu();
	void ShowLevelUpWeaponMenu();
	void ShowLevelUpArmorMenu();
	void ShowBackPackAndWireHouse();
	void ShowWireHouse();
	void ShowWireHousePut();
	void ShowWireHouseGet();
	void ShowTransfer();
	void GoBattle();
	void InitialCareer();
	void Initialize();

	Adventurer* fighter_;
	map<string, void(*)> mapping_function_;
	BattleScence* battle_scence;

	void SplitString(const string& s, vector<string>& v, const string& c);
};
#endif