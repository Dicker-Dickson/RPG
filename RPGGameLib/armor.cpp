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
	cout << "戰士使用盾牌" << GetName() << ", ";
	cout << "防禦力從原本 " << le->GetSP();
	le->AddSP(this->GetDefenseBonus() + level_ * 3);
	cout << "上升到 " << le->GetSP() << endl;
}

void Armor::UnUsed(LifeEntity *le) {
	cout << "戰士 " << GetName() << " ";
	cout << "防禦力從原本 " << le->GetSP();
	le->DelSP(this->GetDefenseBonus() + level_ * 3);
	cout << "下降到 " << le->GetSP() << endl;
}

int Armor::IsA() {
	return ARMOR;
}

int Armor::GetBonous()
{
	return bonus_defense_;
}