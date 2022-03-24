#include <iostream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <sstream>
#include <ctime>
#include <windows.h>
#include "Monster.h"
#include "food.h"
#include "MapData.h"
#include "GlobalInfo.h"
#include "CmdParser.h"
#include "User.h"
#include "MonsterData.h"
#include <limits>
#include "battle_scene.h"
#include "beginner.h"
#include "adventurer_factory.h"
#include "adventurer_data.h"
#include "start_menu.h"
#include "selection_menu.h"
#include "store.h"
#include "wirehouse.h"
#include "skill_data.h"

using namespace std;

ItemData *CGlobalInfo::itm_data = new ItemData;
MapData *CGlobalInfo::map_data = new MapData;
CCmdParser *CGlobalInfo::parser = new CCmdParser;
User *CGlobalInfo::user = new User;
MonsterData *CGlobalInfo::monster_data = new MonsterData();
AdventurerData *CGlobalInfo::adventurer_data = new AdventurerData();
Store * CGlobalInfo::store = new Store();
WireHouse* CGlobalInfo::wire_house = new WireHouse();
SkillData* CGlobalInfo::skill_data = new SkillData();
int Monster::counter_for_monster_id_ = 0;

int main() {
	CGlobalInfo::itm_data->Initialize();
	StartMenu * start_menu = new StartMenu();
	start_menu->ShowMainMenu();
	system("CLS");
	SelectionMenu* selection_menu = new SelectionMenu();
	selection_menu->ShowSelectionMenu();

	system("pause");
	return 0;
}