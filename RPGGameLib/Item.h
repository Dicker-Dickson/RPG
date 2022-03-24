#ifndef ITEM_H
#define ITEM_H

#include <string>

class LifeEntity;
using namespace std;

class Item {
public:
	Item(string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int money = 0);
	void setSize(int);
	int getSize();
	void setWeight(int);
	int getWeight();
	void setName(string);
	string getName();
	int getID() { return ID; };
	virtual int GetBonous() = 0;
	virtual void beUsed(LifeEntity *) = 0;
	virtual void UnUsed(LifeEntity *) = 0;
	virtual int GetLevel();

	virtual int IsA() = 0;
	int GetMoney();

private:
	int ID;
	int Size, Weight;
	string name_;
	int money_;
};

#endif