#ifndef LIFEENTITY_H
#define LIFEENTITY_H

#include <string>
#include "weapon.h"
#include "armor.h"
#include "definition.h"

using namespace std;

class LifeEntity {
public:
	LifeEntity(int initHP = 0, int initSP = 0, int initMP = 0, string initname = "", int initlevel = 0, int initexp = 0);
	void SetInitSPHPMP(int initHP = 0, int initSP = 0, int initMP = 0);
	bool IsDead();
	void SetHP(int);
	void SetMP(int);
	void AddHP(int);
	void AddMP(int);
	void DelMP(int);
	int GetHP();
	int GetMP();
	int GetMaxHP();
	int GetMaxMP();
	void AddMaxHP(int);
	void AddMaxMP(int);
	void AddMaxSP(int);
	int GetSP();
	int GetMaxSP();
	void AddSP(int);

	void DelSP(int);
	void AddDefense(int value);
	int GetHurt(int hurt);
	string GetName();
	void SetName(string);
	Weapon *GetWeapon() { return weapon; };
	Armor * GetArmor() { return armor_; }
	void SetWeapon(Weapon *in_weapon) { weapon = in_weapon; }
	void SetArmor(Armor* in_armor) { armor_ = in_armor; }
	bool Kill(LifeEntity *);
	virtual int Attack(LifeEntity *) = 0;
	virtual int Defense() = 0;
	virtual int IsA() = 0;

	void SetLevel(int level);
	int GetLevel();
	void SetExp(int exp);
	int GetExp();
	void AddExp(int exp);

private:
	void FightStatus(LifeEntity *f, LifeEntity *s);
	void BloodBarShow(string title, int maxvalue, int value);
	int max_sp_, max_hp_, max_mp_;
	int sp_, hp_, mp_;
	int level_;
	int exp_;
	string name_;
	Weapon *weapon;
	Armor* armor_;
};

#endif