#pragma once
#ifndef _COLLISIONS_H
#define _COLLISIONS_H
#include "Commons.h"
class Character;
class Collisions
{
public :
	~Collisions();
	static Collisions* Instance();

	bool Circle(Character* CharacterMario, Character* CharacterLuigi);
	bool Box(Rect2D rect1, Rect2D rect2);
private:
	Collisions();
	static Collisions* mInstance;

};

#endif


