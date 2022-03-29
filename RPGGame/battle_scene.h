#ifndef BATTLE_SCENCE_H
#define BATTLE_SCENCE_H

#include "adventurer.h"
#include "global_info.h"
#include "monster.h"
#include <iostream>
#include <windows.h>
#include "item_data.h"
#include "map_data.h"
#include "user.h"

#define MAXBARLEN 100

class MonsterData;

class BattleScence {
public:
	BattleScence();
	~BattleScence();
	void askforbaglist(Adventurer *f);
	Monster *MonsterSelection(Adventurer *f);
	void BloodBarShow(int maxhp, int hp);
	void FightStatus(Monster *m, Adventurer *f);
	void fightshow(Monster *m, Adventurer *f);
	void startfight(Monster *m, Adventurer *f);
private:
};

#endif