#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>
#include <iostream>
#include "global_info.h"
#include <fstream>
#include "skill_data.h"

using namespace std;

class Skill {
public:
	Skill(SkillAttribute);
	~Skill();

	string GetCareer();
	string GetSkillName();
	int GetMP();
	string GetMethod();
	vector<int> GetValue();
	int GetLevel();
	void AddLevel(int);
	int GetSkillValue();

private:
	string career_;
	string name_;
	int mp_;
	string method_;
	vector<int> value_;
	int skill_level_;
};

#endif