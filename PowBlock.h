#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H
#include <SDL.h>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include <string>
#include <iostream>
#include "GameScreenLevel1.h"
class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();
	void Render();
    Rect2D GetCollisionBox();
	void TakeAHit();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; };
	void UpdatePowBlock();
private:
	SDL_Renderer* mRenderer;
	Vector2D  mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float   mSingleSpriteWidth;
	float   mSingleSpriteHeight;

	int  mNumberOfHitsLeft;
};
#endif
