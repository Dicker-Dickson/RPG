#include <iostream>
#include "item.h"
#include "food.h"
#include "life_entity.h"
#include "definition.h"

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

void Food::BeUsed(LifeEntity *le) {
	cout << "�ϥέ���" << GetName() << ", ";
	le->AddHP(this->gethpbonus());
	cout << "��O�^�ɨ� " << le->GetHP() << endl;
}

void Food::UnUsed(LifeEntity *le) {
}

int Food::IsA() {
	return FOOD;
}