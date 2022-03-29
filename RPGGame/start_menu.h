#ifndef START_MENU_H
#define START_MENU_H

#include "global_info.h"
#include "adventurer_data.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <direct.h>
#include <sstream>
#include "wirehouse.h"

#define MAXBARLEN 40

using namespace std;

struct UserData {
	string name;
	string password;
};

class StartMenu {
public:
	StartMenu();
	~StartMenu();

	void ShowMainMenu();
	void SignUp();
	void LogIn();
	void ChoiseAdventurer();

	void NewFolder(string path);
	string GetUser();
	int GetUserId();
	vector<UserData> user_data_;

	string user_name_;
	int user_id_;
};

#endif