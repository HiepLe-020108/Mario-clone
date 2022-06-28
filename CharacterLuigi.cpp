#include "CharacterLuigi.h"
#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include <SDL.h>
#include <iostream>
#include <string>
using std::string;
using namespace::std;


CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startposition, LevelMap* map) :
	Character(renderer, imagePath, startposition, map) {

}
CharacterLuigi::~CharacterLuigi() {

}

void CharacterLuigi::Update(float deltaTime, SDL_Event e) {
	/*if (mPosition.y < 340) {
		AddGravity(deltaTime);
		mCanJump = false;
	}
	else {
		mCanJump = true;
	}*/

	Character::Update(deltaTime, e);

	
	/*if (mJumping) {
		mCanJump = false;
		mPosition.y -= mJumpForce * deltaTime;

		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}*/
	if (mMovingLeft) {
		MoveLeft(deltaTime);
		mFacingDirection = FACING_RIGHT;
	}
	else if (mMovingRight) {
		MoveRight(deltaTime);
		mFacingDirection = FACING_LEFT;
	}
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;

		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			mMovingRight = false;
			mMovingLeft = true;
			break;
		case SDLK_d:
			mMovingLeft = false;
			mMovingRight = true;
			break;
		case SDLK_w:
			Jump();
			break;
		default:
			break;
		}
		break;
	}
}
Rect2D CharacterLuigi::GetCollisionBox() {
	
		return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
	}

