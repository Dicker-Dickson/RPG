#include "cmd_parser.h"

int FunctionExit(vector<string> &tokens) {
	return -1;
}

int FunctionMoveCity(vector<string> &tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}

	int place = 0;
	string dir = tokens[0];
	if (dir == string("�����q")) {
		place = 1;
	}
	else if (dir == string("���h�Q�ȴ�")) {
		place = 2;
	}
	else if (dir == string("�i�h����")) {
		place = 3;
	}
	else if (dir == string("�}�b���")) {
		place = 4;
	}
	else if (dir == string("�]�k�˪L")) {
		place = 5;
	}
	else if (dir == string("�Z������")) {
		place = 6;
	}
	else {
		cout << "no such command " << dir << endl;
		return 0;
	}

	int NextPlace = CGlobalInfo::user->MoveCity(place);
	if (NextPlace) {
		system("cls");
		CGlobalInfo::map_data->ShowDescription(NextPlace);
	}
	else {
		cout << "����S����!!!�д��Ӥ�V�a" << endl;
	}
	return 0;
}

int FunctionNextDirection(vector<string> &tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}
	int next_direction = 0;
	string dir = tokens[0];
	if (dir == string("east")) {
		next_direction = EAST;
	}
	else if (dir == string("west")) {
		next_direction = WEST;
	}
	else if (dir == string("north")) {
		next_direction = NORTH;
	}
	else if (dir == string("south")) {
		next_direction = SOUTH;
	}
	else if (dir == string("eastnorth")) {
		next_direction = EAST_NORTH;
	}
	else if (dir == string("eastsouth")) {
		next_direction = EAST_SOUTH;
	}
	else if (dir == string("westnorth")) {
		next_direction = WEST_NORTH;
	}
	else if (dir == string("westsouth")) {
		next_direction = WEST_SOUTH;
	}
	else {
		cout << "no such command " << dir << endl;
		return 0;
	}

	int NextPlace = CGlobalInfo::user->goto_NextCity(next_direction);
	if (NextPlace) {
		system("cls");
		CGlobalInfo::map_data->ShowDescription(NextPlace);
	}
	else {
		cout << "����S����!!!�д��Ӥ�V�a" << endl;
	}
	return 0;
}

CmdParser::CmdParser() {
	mapping_function_[string("exit")] = FunctionExit;
	mapping_function_[string("east")] = FunctionNextDirection;
	mapping_function_[string("eastnorth")] = FunctionNextDirection;
	mapping_function_[string("eastsouth")] = FunctionNextDirection;
	mapping_function_[string("west")] = FunctionNextDirection;
	mapping_function_[string("westsouth")] = FunctionNextDirection;
	mapping_function_[string("westnorth")] = FunctionNextDirection;
	mapping_function_[string("north")] = FunctionNextDirection;
	mapping_function_[string("south")] = FunctionNextDirection;
	mapping_function_[string("�����q")] = FunctionMoveCity;
	mapping_function_[string("���h�Q�ȴ�")] = FunctionMoveCity;
	mapping_function_[string("�i�h����")] = FunctionMoveCity;
	mapping_function_[string("�}�b���")] = FunctionMoveCity;
	mapping_function_[string("�]�k�˪L")] = FunctionMoveCity;
	mapping_function_[string("�Z������")] = FunctionMoveCity;
}

CmdParser::~CmdParser()
{
}

int CmdParser::Query() {
	string sentense;
	getline(cin, sentense);
	vector<string> tokens;
	SplitString(sentense, tokens, string(" "));
	if (tokens.size() == 0) {
		return 0;
	}

	map<string, void(*)>::iterator it;
	it = mapping_function_.find(tokens[0]);
	if (it == mapping_function_.end()) {
		cout << "no such commands" << endl;
		return 0;
	}
	return (reinterpret_cast<int(*)(const vector<string> &)>(it->second)(tokens));
}

void CmdParser::SplitString(const string& s, vector<string>& v, const string& c)
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