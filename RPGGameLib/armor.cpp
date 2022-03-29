#include <iostream>
#include "item.h"
#include "armor.h"
#include "life_entity.h"
#include "definition.h"

using namespace std;

Armor::Armor(string inname, int initSize, int initWeight, int initID, int init_defense, int money, int level)
	:Item(inname, initSize, initWeight, initID, money) {
	bonus_defense_ = init_defense;
	level_ = level;
}

int Armor::GetDefenseBonus() {
	return bonus_defense_;
}

void Armor::AddLevel(int l)
{
	level_ += l;
}

int Armor::GetLevel()
{
	return level_;
}

void Armor::SetLevel(int l)
{
	level_ = l;
}

void Armor::BeUsed(LifeEntity *le) {
	cout << "�Ԥh�ϥά޵P" << GetName() << ", ";
	cout << "���m�O�q�쥻 " << le->GetSP();
	le->AddSP(this->GetDefenseBonus() + level_ * 3);
	cout << "�W�ɨ� " << le->GetSP() << endl;
}

void Armor::UnUsed(LifeEntity *le) {
	cout << "�Ԥh " << GetName() << " ";
	cout << "���m�O�q�쥻 " << le->GetSP();
	le->DelSP(this->GetDefenseBonus() + level_ * 3);
	cout << "�U���� " << le->GetSP() << endl;
}

int Armor::IsA() {
	return ARMOR;
}

int Armor::GetBonous()
{
	return bonus_defense_;
}