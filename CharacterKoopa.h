#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H
#include <SDL.h>
#include "LevelMap.h"
#include "Texture2D.h "
#include "Character.h"
class Character;
class CharacterKoopa: public Character

{
public :
	 CharacterKoopa(SDL_Renderer* renderer, string imagePath,
		LevelMap* map, Vector2D startPosition, FACING startFacing,
		float movementSpeed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Update(float deltaTime, SDL_Event e);
	void Render();
	bool GetInjured();
private:

	void FlipRightwayUp();


	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mInjured;
	float mInjuredTime;

};

#endif