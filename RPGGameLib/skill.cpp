#include "stdafx.h"
#include "skill.h"

Skill::Skill(SkillAttribute a)
{
	career_ = a.career;
	name_ = a.name;
	mp_ = stoi(a.mp);
	method_ = a.method;
	value_ = a.value;
	skill_level_ = a.level;
}

Skill::~Skill()
{
}

string Skill::GetCareer()
{
	return career_;
}

string Skill::GetSkillName()
{
	return name_;
}

int Skill::GetMP()
{
	return mp_;
}

string Skill::GetMethod()
{
	return method_;
}

vector<int> Skill::GetValue()
{
	return value_;
}

int Skill::GetLevel()
{
	return skill_level_ + 1;
}

void Skill::AddLevel(int i)
{
	i + skill_level_ < 10 ? skill_level_ += i : skill_level_;
}

int Skill::GetSkillValue()
{
	return value_[skill_level_];
}