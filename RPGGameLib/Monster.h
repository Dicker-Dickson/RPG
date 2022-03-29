//Monster is a child from LifeEntity. Monster battle with adventurer. It create from Place object
//How to use:
//1. Create Monster
//MonsterType *type = CGlobalInfo::monster_data->GetMonstertypeById(place_id);
//Monster *mon = new Monster(type);
//2. Attack
//LifeEntity* b;
//mon->Attack(b);

#ifndef MONSTER_H
#define MONSTER_H

#include "life_entity.h"
class MonsterType;

class Monster : public LifeEntity {
public:
	Monster(int initHP = 0, int initSP = 0, int initMP = 0, int initrough = 0, string init_name = string("й╟кл"), string init_eng_name_ = string("monster"));
	Monster(const MonsterType *type);

	/// <summary> Get rought</summary>
	/// <returns>int type, return is rough</returns>
	int GetRough();

	/// <summary> Attack (attack value = damage - defense)</summary>
	/// <param name="life"> LifeEntity* type, input: life </param>
	/// <returns>int type, return is monster attack value</returns>
	virtual int Attack(LifeEntity * life) override;
	/// <summary> Defense </summary>
	/// <returns>int type, return is monster defense value</returns>
	virtual int Defense()override;

	/// <summary> Tell you what is it? </summary>
	/// <returns>int type, return is MONSTER</returns>
	virtual int IsA() override;

	/// <summary> Get monsters id </summary>
	/// <returns>int type, return is monster id</returns>
	int GetMonsterId();
private:
	int PhysicalDamage();

	static int counter_for_monster_id_;
	int rough_degree_;
	int id_;
};

#endif