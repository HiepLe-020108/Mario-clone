#include "CharacterMario.h"
#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include <SDL.h>
#include <iostream>
#include <string>
using std::string;
using namespace::std;

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startposition, LevelMap* map) 
	: Character(renderer, imagePath, startposition, map) {

}
CharacterMario::~CharacterMario() {

}



void CharacterMario::Update(float deltaTime, SDL_Event e) {
	/*if (mPosition.y < 340) {
		AddGravity(deltaTime);
		mCanJump = false;
	}
	else {
		mCanJump = true;
	}*/

	Character::Update(deltaTime, e);

	GetCollisionRadius();
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
	}
	else if (mMovingRight) {
		MoveRight(deltaTime);
	}

	//Get the events
	SDL_PollEvent(&e);

	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			mMovingRight = false;
			mMovingLeft = true;
			break;
		case SDLK_RIGHT:
			mMovingLeft = false;
			mMovingRight = true;
			break;
		case SDLK_UP:
			Jump();
			break;
		default:
			break;
		}
		break;
	}
}
Rect2D CharacterMario::GetCollisionBox() {
	
		return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
	}




