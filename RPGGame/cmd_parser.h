//CmdParser is like as cmd. you can type command to control where the place you want to move
//For example, type "move ¼Z¸¨«°¥«" you will move to "¼Z¸¨«°¥«".
//or you can type "move south" if the south direction has a place.
//How to use:
//I set it to the global. You can type the command when adventurer in the map.

#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include "global_info.h"
#include "user.h"
#include "map_data.h"
#include "definition.h"

using namespace std;

class CmdParser {
public:
	CmdParser();
	~CmdParser();

	/// <summary>Query this object and type command line </summary>
	/// <returns> int type, return 1 is success 0 is false</returns>
	int Query();
private:
	void SplitString(const string& s, vector<string>& v, const string& c);
	map<string, void(*)> mapping_function_;
};

#endif