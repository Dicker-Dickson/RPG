#include "Item.h"

Item::Item(string inname, int initSize, int initWeight, int initID, int money) {
	name_ = inname;
	Size = initSize;
	Weight = initWeight;
	ID = initID;
	money_ = money;
}

void Item::setSize(int inSize) {
	Size = inSize >= 0 ? inSize : 0;
}

void Item::setWeight(int inWeight) {
	Weight = inWeight >= 0 ? inWeight : 0;
}

void Item::setName(string inName) {
	name_ = inName;
}

int Item::getSize() {
	return Size;
}

int Item::getWeight() {
	return Weight;
}

string Item::getName() {
	return name_;
}

int Item::GetLevel()
{
	return 0;
}

int Item::GetMoney()
{
	return money_;
}