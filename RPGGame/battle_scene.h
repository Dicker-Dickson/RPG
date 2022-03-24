#ifndef BATTLE_SCENCE_H
#define BATTLE_SCENCE_H

#include "adventurer.h"
#include "GlobalInfo.h"
#include "Monster.h"
#include <iostream>
#include <windows.h>
#include "ItemData.h"
#include "MapData.h"
#include "User.h"

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