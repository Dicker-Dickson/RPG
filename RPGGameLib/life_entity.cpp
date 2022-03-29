#include <iostream>
#include <Windows.h>
#include "global_info.h"
#include "life_entity.h"

LifeEntity::LifeEntity(int initHP, int initSP, int initMP, string initname, int initlevel, int initexp) {
	max_sp_ = sp_ = initSP;
	max_hp_ = hp_ = initHP;
	max_mp_ = mp_ = initMP;
	name_ = initname;
	weapon = NULL;
	level_ = initlevel;
	exp_ = initexp;
}

void LifeEntity::SetInitSPHPMP(int initHP, int initSP, int initMP) {
	max_sp_ = sp_ = initSP;
	max_hp_ = hp_ = initHP;
	max_mp_ = mp_ = initMP;
}

void LifeEntity::SetHP(int inHP) {
	hp_ = inHP > max_hp_ ? max_hp_ : inHP;
}

void LifeEntity::SetMP(int inMP)
{
	mp_ = inMP > max_mp_ ? max_mp_ : inMP;
}

void LifeEntity::AddHP(int inHP) {
	hp_ = (inHP + hp_) > max_hp_ ? max_hp_ : (hp_ + inHP);
}

void LifeEntity::AddMP(int inMP)
{
	mp_ = (inMP + mp_) > max_mp_ ? max_mp_ : (mp_ + inMP);
}

void LifeEntity::DelMP(int inMP)
{
	mp_ -= inMP;
}

void LifeEntity::AddSP(int inSP) {
	sp_ = inSP + sp_;
}

void LifeEntity::DelSP(int inSP) {
	sp_ -= inSP;
}

int LifeEntity::GetHP() {
	return (hp_ > 0 ? hp_ : 0);
}

int LifeEntity::GetMP()
{
	return (mp_ > 0 ? mp_ : 0);
}

int LifeEntity::GetMaxHP() {
	return (max_hp_);
}

int LifeEntity::GetMaxMP()
{
	return (max_mp_);
}

void LifeEntity::AddMaxHP(int hp)
{
	max_hp_ += hp;
}

void LifeEntity::AddMaxMP(int mp)
{
	max_mp_ += mp;
}

void LifeEntity::AddMaxSP(int p)
{
	max_sp_ += p;
}

int LifeEntity::GetSP() {
	return sp_;
}

int LifeEntity::GetMaxSP() {
	return (max_sp_);
}

bool LifeEntity::IsDead() {
	return (hp_ <= 0);
}

int  LifeEntity::GetHurt(int hurt) {
	if (hurt > hp_)
		SetHP(0);
	else if (hurt > 0)
		SetHP(hp_ - hurt);
	return hp_;
}

string LifeEntity::GetName() {
	return name_;
}

void LifeEntity::SetName(string inname) {
	name_ = inname;
}

bool LifeEntity::Kill(LifeEntity *enemy) {
	int f_damage = 0, s_damage = 0;
	LifeEntity *first, *second;
	int whofirst;
	while (!this->IsDead() && !enemy->IsDead()) {
		whofirst = rand() % 2;
		if (whofirst == 0) {
			cout << "對方搶得先機，先出手傷人" << endl;
			first = (LifeEntity *)enemy;
			second = (LifeEntity *) this;
		}
		else {
			cout << "你搶得先機，先出手傷人" << endl;
			first = (LifeEntity *) this;
			second = (LifeEntity *)enemy;
		}

		s_damage = first->Attack(second);
		FightStatus(enemy, this);
		if (second->IsDead()) {
			Sleep(1000);
			break;
		}
		f_damage = second->Attack(first);
		FightStatus(enemy, this);
		Sleep(2000);
	}
	if (this->IsDead())
		return 0;
	return 1;
}

void LifeEntity::SetLevel(int level)
{
	level_ = level;
}

int LifeEntity::GetLevel()
{
	return level_;
}

void LifeEntity::SetExp(int exp)
{
	exp_ = exp;
}

void LifeEntity::FightStatus(LifeEntity *f, LifeEntity *s) {
	cout << endl << f->GetName() << endl;
	BloodBarShow(string("hp_"), f->GetMaxHP(), f->GetHP());
	cout << s->GetName() << endl;
	BloodBarShow(string("hp_"), s->GetMaxHP(), s->GetHP());
	cout << endl;
}

void LifeEntity::BloodBarShow(string title, int maxvalue, int value) {
	cout << title << "     |";
	float hpslotlen = (float)maxvalue / 40;
	int numhp = (int)ceil(value / hpslotlen);
	for (int i = 0; i < numhp; i++) {
		cout << "#";
	}
	numhp = (int)floor((maxvalue - value) / hpslotlen);
	for (int i = 0; i < numhp; i++) {
		cout << " ";
	}
	cout << "|" << endl;
}

int LifeEntity::GetExp() {
	return exp_;
}

void LifeEntity::AddExp(int exp)
{
	exp_ = exp_ + exp;
}