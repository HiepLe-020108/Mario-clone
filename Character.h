#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include <SDL.h>
#include <iostream>
#include "commons.h"
#include <string>
#include "LevelMap.h"
using namespace std;
class Texture2D;
class Character
{
public :
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void AddGravity(float deltaTime);
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump();

	Rect2D GetCollisionBox();

	void         SetPosition(Vector2D newPosition);
	Vector2D     GetPosition();
	float GetCollisionRadius();
	FACING mFacingDirection;
	bool   mMovingLeft;
	bool   mMovingRight;
	bool   mMoveDown;
	bool  mJumping;
	bool  mCanJump;
	float mJumpForce;
	bool isAlive;
	
	float mMovementSpeed;

	bool IsJumping();
	void CancelJump();

	void SetAlive(bool mIsAlive);
	bool GetAlive();
private:
	int footPosition;
	int centralXPosition;

	LevelMap* mCurrentMap;
protected:
	SDL_Renderer* mRenderer;
	Vector2D      mPosition;
	Texture2D*    mTexture;
	float mCollisionRadius;
	
	
};
#endif


