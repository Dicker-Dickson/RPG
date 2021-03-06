#ifndef USER_H
#define USER_H

#include <string>
#include "life_entity.h"

using namespace std;

class User {
public:
	User();
	void set_user(LifeEntity *in_usr);
	int goto_NextCity(int next);
	int get_current_city();
	int MoveCity(int place);
	LifeEntity* get_user() { return user; };
private:
	LifeEntity *user;
};

#endif