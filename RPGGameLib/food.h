#ifndef FOOD_H
#define FOOD_H

#include "Item.h"

class Food : public Item {
public:
	Food(string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_hp = 0, int money = 0);
	int gethpbonus();
	virtual int GetBonous() override;
	virtual void beUsed(LifeEntity *);
	virtual void UnUsed(LifeEntity *);
	virtual int IsA();

private:
	int bonus_hp;
};

#endif