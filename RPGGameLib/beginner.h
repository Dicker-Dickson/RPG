#ifndef BEGINNER_H
#define BEGINNER_H

#include "adventurer.h"
#include <iostream>
#include "def.h"
using namespace std;

class Beginner : public Adventurer
{
public:
	Beginner();
	~Beginner();

	virtual bool IsLevelUp() override;
	virtual int PhysicalDamage() override;

	virtual void ShowCareer() override;
	virtual void LearnSkill(int) override;
	virtual int IsA() override;
	virtual int GetSkillNumber() override;
	virtual void UseSkillById(LifeEntity *l, int id) override;
	virtual int SkillUseMP(int id) override;
	virtual void LearnSkill(SkillAttribute skill) override;
};

#endif