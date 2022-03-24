#include <iostream>
#include "Item.h"
#include "food.h"
#include "LifeEntity.h"
#include "def.h"

using namespace std;

Food::Food(string inname, int initSize, int initWeight, int initID, int init_hp, int money) : Item(inname, initSize, initWeight, initID, money) {
	bonus_hp = init_hp;
}

int Food::gethpbonus() {
	return bonus_hp;
}

int Food::GetBonous()
{
	return bonus_hp;
}

void Food::beUsed(LifeEntity *le) {
	cout << "�ϥέ���" << getName() << ", ";
	le->AddHP(this->gethpbonus());
	cout << "��O�^�ɨ� " << le->GetHP() << endl;
}

void Food::UnUsed(LifeEntity *le) {
}

int Food::IsA() {
	return efood;
}