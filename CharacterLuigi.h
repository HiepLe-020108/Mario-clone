#pragma once
#ifndef _CHARACTELUIGI_H
#define _CHARACTERLUIGI_H
#include "Character.h"
class Character;
class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	// void Render();
	void Update(float deltaTime, SDL_Event e);
	Rect2D GetCollisionBox();
};
#endif
