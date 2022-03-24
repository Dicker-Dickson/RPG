#include <iostream>
#include <string>
#include <cassert>
#include "Place.h"
#include "CmdParser.h"
#include "GlobalInfo.h"
#include "User.h"
#include "MapData.h"
#include "adventurer.h"
#include "def.h"
#include "ItemData.h"

int function_exit(vector<string> &tokens) {
	return -1;
}

int function_move_city(vector<string> &tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}

	int city = 0;
	string dir = tokens[0];
	if (dir == string("�����q")) {
		city = 1;
	}
	else if (dir == string("���h�Q�ȴ�")) {
		city = 2;
	}
	else if (dir == string("�i�h����")) {
		city = 3;
	}
	else if (dir == string("�}�b���")) {
		city = 4;
	}
	else if (dir == string("�]�k�˪L")) {
		city = 5;
	}
	else if (dir == string("�Z������")) {
		city = 6;
	}
	else {
		cout << "no such command " << dir << endl;
		return 0;
	}

	int NextCity = CGlobalInfo::user->MoveCity(city);
	if (NextCity) {
		system("cls");
		CGlobalInfo::map_data->ShowDescription(NextCity);
	}
	else {
		cout << "����S����!!!�д��Ӥ�V�a" << endl;
	}
	return 0;
}

int function_next_direction(vector<string> &tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}
	int next_dir = 0;
	string dir = tokens[0];
	if (dir == string("east")) {
		next_dir = eEast;
	}
	else if (dir == string("west")) {
		next_dir = eWest;
	}
	else if (dir == string("north")) {
		next_dir = eNorth;
	}
	else if (dir == string("south")) {
		next_dir = eSouth;
	}
	else if (dir == string("eastnorth")) {
		next_dir = eEastNorth;
	}
	else if (dir == string("eastsouth")) {
		next_dir = eEastSouth;
	}
	else if (dir == string("westnorth")) {
		next_dir = eWestNorth;
	}
	else if (dir == string("westsouth")) {
		next_dir = eWestSouth;
	}
	else {
		cout << "no such command " << dir << endl;
		return 0;
	}

	int NextCity = CGlobalInfo::user->goto_NextCity(next_dir);
	if (NextCity) {
		system("cls");
		CGlobalInfo::map_data->ShowDescription(NextCity);
	}
	else {
		cout << "����S����!!!�д��Ӥ�V�a" << endl;
	}
	return 0;
}

CCmdParser::CCmdParser() {
	mappingfunc[string("exit")] = function_exit;
	mappingfunc[string("east")] = function_next_direction;
	mappingfunc[string("eastnorth")] = function_next_direction;
	mappingfunc[string("eastsouth")] = function_next_direction;
	mappingfunc[string("west")] = function_next_direction;
	mappingfunc[string("westsouth")] = function_next_direction;
	mappingfunc[string("westnorth")] = function_next_direction;
	mappingfunc[string("north")] = function_next_direction;
	mappingfunc[string("south")] = function_next_direction;
	mappingfunc[string("�����q")] = function_move_city;
	mappingfunc[string("���h�Q�ȴ�")] = function_move_city;
	mappingfunc[string("�i�h����")] = function_move_city;
	mappingfunc[string("�}�b���")] = function_move_city;
	mappingfunc[string("�]�k�˪L")] = function_move_city;
	mappingfunc[string("�Z������")] = function_move_city;
}

int CCmdParser::query() {
	string sentense;
	getline(cin, sentense);
	vector<string> tokens;
	splitstring(sentense, tokens, string(" "));
	if (tokens.size() == 0) {
		return 0;
	}

	map<string, void(*)>::iterator it;
	it = mappingfunc.find(tokens[0]);
	if (it == mappingfunc.end()) {
		cout << "no such commands" << endl;
		return 0;
	}
	return (reinterpret_cast<int(*)(const vector<string> &)>(it->second)(tokens));
}

void CCmdParser::splitstring(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find_first_of(c);
	pos1 = 0;
	while (string::npos != pos2) {
		if (pos2 - pos1)
			v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
		pos2 = s.find_first_of(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}