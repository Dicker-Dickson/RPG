#ifndef SKILL_DATA_H
#define SKILL_DATA_H

#include <string>
#include <vector>
#include <iostream>
#include "global_info.h"
#include <fstream>

using namespace std;

struct SkillAttribute {
	string career;
	string name;
	string mp;
	string method;
	vector<int> value;
	int level;
};

class SkillData {
public:
	SkillData();
	~SkillData();
	void Load();
	vector<SkillAttribute> GenerateSkill();
	void ShowSkillList();
	void ShowWarriorSkill();
	void ShowMagicianSkill();
	void ShowThiefSkill();
	void ShowArcherSkill();

private:
	vector<SkillAttribute> skill_;
};

#endif