#include <iostream>
#include "life_entity.h"
#include "user.h"
#include "definition.h"
#include "adventurer.h"

User::User() {
	user = NULL;
};

void User::set_user(LifeEntity *in_usr) {
	user = in_usr;
}

int User::goto_NextCity(int next) {
	return ((Adventurer *)user)->GoToNextCity(next);
}

int User::get_current_city() {
	return ((Adventurer *)user)->GetCurrentCity();
}

int User::MoveCity(int place)
{
	return ((Adventurer *)user)->MoveCity(place);
}