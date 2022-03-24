#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item {
public:
	Weapon(string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_Attack = 0, int money = 0, int level = 0);
	int getAttackbonus();
	virtual int GetLevel() override;
	void AddLevel(int);
	void SetLevel(int);
	virtual void beUsed(LifeEntity *);
	virtual void UnUsed(LifeEntity *);
	virtual int IsA();
	virtual int GetBonous() override;
private:
	int bonus_Attack;
	int level_;
};

#endif