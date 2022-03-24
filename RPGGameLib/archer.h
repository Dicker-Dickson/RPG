#ifndef ARCHER_H
#define ARCHER_H

#include "adventurer.h"
#include <iostream>
#include "def.h"

using namespace std;

class Skill;

class Archer : public Adventurer
{
public:
	Archer();
	~Archer();

	virtual bool IsLevelUp() override;
	virtual int PhysicalDamage() override;
	virtual void ShowCareer() override;
	virtual void LearnSkill(int) override;
	virtual void LearnSkill(SkillAttribute skill) override;
	virtual void ShowSkill();
	virtual int GetSkillNumber() override;
	virtual void UseSkillById(LifeEntity *l, int id) override;
	virtual int SkillUseMP(int id) override;
	virtual vector<Skill*> GetSkill();
	virtual int IsA() override;
	vector<Skill*> skill_;
};

#endif