#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H
#include "Character.h"
class Character;
class CharacterMario :  public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	// void Render();
	 void Update(float deltaTime, SDL_Event e);
	 Rect2D GetCollisionBox();
		 
};
#endif

