#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"

class Armor : public Item {
public:
	Armor(string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_defense = 0, int money = 0, int level = 0);
	int GetDefenseBonus();
	void AddLevel(int);
	virtual int GetLevel() override;
	void SetLevel(int);
	virtual void BeUsed(LifeEntity *);
	virtual void UnUsed(LifeEntity *);
	virtual int IsA() override;
	virtual int GetBonous() override;
private:
	int bonus_defense_;
	int level_;
};

#endif