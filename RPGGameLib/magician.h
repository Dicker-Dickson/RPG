#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "adventurer.h"
#include <iostream>
#include "definition.h"

using namespace std;

class Skill;

class Magician : public Adventurer
{
public:
	Magician();
	~Magician();

	virtual bool IsLevelUp() override;
	virtual int PhysicalDamage() override;
	virtual void ShowCareer() override;
	virtual void LearnSkill(int) override;
	virtual void LearnSkill(SkillAttribute skill) override;
	virtual void ShowSkill()override;
	virtual int IsA() override;
	virtual int GetSkillNumber() override;
	virtual void UseSkillById(LifeEntity *l, int id) override;
	virtual int SkillUseMP(int id) override;
	virtual vector<Skill*> GetSkill();
private:
	vector<Skill*> skill_;
};

#endif