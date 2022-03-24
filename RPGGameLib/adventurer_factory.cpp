#include "adventurer_factory.h"
#include "beginner.h"
#include "warrior.h"
#include "magician.h"
#include "thief.h"
#include "archer.h"

AdventurerFactory::AdventurerFactory()
{
}

AdventurerFactory::~AdventurerFactory()
{
}

Adventurer* WarriorFactory::CreateAdventure()
{
	return new Warrior();
}

Adventurer * BeginnerFactory::CreateAdventure()
{
	return new Beginner();
}

Adventurer * MagicianFactory::CreateAdventure()
{
	return new Magician();
}

Adventurer * ThiefFactory::CreateAdventure()
{
	return new Thief();
}

Adventurer * ArcherFactory::CreateAdventure()
{
	return new Archer();
}