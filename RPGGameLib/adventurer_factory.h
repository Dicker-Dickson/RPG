#ifndef ADVENTURER_FACTORY_H
#define ADVENTURER_FACTORY_H

#include "adventurer.h"

class Beginner;
class Warrior;
class Magician;
class Thief;
class Archer;

class AdventurerFactory
{
public:
	AdventurerFactory();
	~AdventurerFactory();
	virtual Adventurer* CreateAdventure() = 0;
};

class BeginnerFactory : public AdventurerFactory
{
public:
	virtual Adventurer* CreateAdventure() override;
};

class WarriorFactory : public AdventurerFactory
{
public:
	virtual Adventurer* CreateAdventure() override;
};

class MagicianFactory : public AdventurerFactory
{
public:
	virtual Adventurer* CreateAdventure() override;
};

class ThiefFactory : public AdventurerFactory
{
public:
	virtual Adventurer* CreateAdventure() override;
};

class ArcherFactory : public AdventurerFactory
{
public:
	virtual Adventurer* CreateAdventure() override;
};

#endif