//Item is a parent of food, weapon and armor. It a basic object in the BagEntry
//How to use:
//1. Initial
//string name;
//int inID, defense_bonus, money, level;
//Item * item = new Armor(name, 0, 0, inID, defense_bonus, money, level);
//2. Get Name
//auto name = item->GetName();
//3. Get Money
//auto money = item->GetMoney();
//4. Get Level
//auto level  =  item->GetLevel();
//5. Get ID
//auto id = item->GetID();
//6. Get Bonous
//auto bonous = item->GetBonous();
//7. Change beused/unused status(weapon, armor)
//LifeEntity* life;
//item->BeUsed(life);
//item->Unused(life);

#ifndef ITEM_H
#define ITEM_H

#include <string>

class LifeEntity;
using namespace std;

class Item {
public:

	Item(string in_name = "", int init_size = 0, int init_weight = 0, int init_id = 0, int money = 0);
	~Item();

	/// <summary> Set size </summary>
	/// <param name="in_size"> int type, input: item size </param>
	/// <returns> void type</returns>
	void SetSize(int in_size);

	/// <summary> Get size </summary>
	/// <returns> int type, return is item size</returns>
	int GetSize();

	/// <summary> Set weight </summary>
	/// <param name="in_weight"> int type, input: item weight </param>
	/// <returns> void type</returns>
	void SetWeight(int in_weight);

	/// <summary> Get weight </summary>
	/// <returns> int type, return is item weight</returns>
	int GetWeight();

	/// <summary> Set name </summary>
	/// <param name="in_name"> int type, input: item name </param>
	/// <returns> void type</returns>
	void SetName(string in_name);

	/// <summary> Get name </summary>
	/// <returns> string type, return is name</returns>
	string GetName();

	/// <summary> Get id </summary>
	/// <returns> int type, return is item id</returns>
	int GetID();

	/// <summary> Get bonous(pure virtual function)</summary>
	/// <returns> int type, return is bonous</returns>
	virtual int GetBonous() = 0;

	/// <summary> Check item is be used(pure virtual function)</summary>
	/// <param name="life"> LifeEntity * type, input: lifeentity </param>
	/// <returns> void type</returns>
	virtual void BeUsed(LifeEntity *life) = 0;

	/// <summary> Check item is unused(pure virtual function)</summary>
	/// <param name="life"> LifeEntity * type, input: lifeentity </param>
	/// <returns> void type</returns>
	virtual void UnUsed(LifeEntity *) = 0;

	/// <summary> Get item level</summary>
	/// <returns> int type</returns>
	virtual int GetLevel();

	/// <summary> Tell you what is it(pure virtual function)</summary>
	/// <returns> int type, return is definition(definition.h)</returns>
	virtual int IsA() = 0;

	/// <summary> Get money</summary>
	/// <returns> int type, return is money</returns>
	int GetMoney();

private:
	int id_;
	int size_, weight_;
	string name_;
	int money_;
};

#endif