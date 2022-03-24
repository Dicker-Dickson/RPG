#ifndef MONSTER_H
#define MONSTER_H

#include "LifeEntity.h"
class MonsterType;

class Monster : public LifeEntity {
public:
	Monster(int initHP = 0, int initSP = 0, int initMP = 0, int initrough = 0, string init_name = string("й╟кл"), string init_eng_name_ = string("monster"));
	Monster(const MonsterType *type);
	int GetRough();
	int PhysicalDamage();
	virtual int Attack(LifeEntity *) override;
	virtual int Defense()override;
	virtual int IsA();
	string GetBasicData();
	string GetEngname() { return eng_name_; };
	int GetMonsterId();
private:
	static int counter_for_monster_id_;
	string eng_name_;
	int rough_degree_;
	int id_;
};

#endif