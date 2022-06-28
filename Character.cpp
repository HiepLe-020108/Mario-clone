#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include <SDL.h>
#include <iostream>
#include <string>
using std::string;
using namespace::std;

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) {
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	mCollisionRadius = 15.0f;



	mCurrentMap = map;
	

}
Character::~Character() {
    mRenderer = NULL;
	}

 void Character::Render() {
  //Texture->Render(mPosition,SDL_FLIP_NONE);
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else {
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
	}
 void Character::Update(float deltaTime, SDL_Event e) {
	
	 //Collision position variables 
	 int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	 int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
	 
	 if (mJumping) {

		 mCanJump = false;

		 mPosition.y -= mJumpForce * deltaTime;

		 mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		 if (mJumpForce <= 0.0f)
		 {
			 mJumping = false;
		 }
	 }
	 //deal with gravity 
	 if (mCurrentMap->GetTileAt(footPosition, centralXPosition) == 0) {
		 AddGravity(deltaTime);
	 }
	 else {
		 //Collided with ground so we can jump again
		 mCanJump = true;
	 }

	 

	 // if (mPosition.y < 340) {
	//	 AddGravity( deltaTime);
	// }
	// if (mJumping) {
	//	 mPosition.y -= mJumpForce * deltaTime;
//
	//	 mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
//
	//	 if (mJumpForce <= 0.0f)
	//	 {
	//		 mJumping = false;
	//	 }
	// }
	// if (mMovingLeft) {
	//	 MoveLeft(deltaTime);
	// }
	// else if (mMovingRight) {
	//	 MoveRight(deltaTime);
	// }
	// switch (e.type) {
	// case SDL_KEYUP:
	//	 switch (e.key.keysym.sym) {
	//	 case SDLK_LEFT:
	//		 mMovingLeft = false;
	//		 break;
	//	 case SDLK_RIGHT:
	//		 mMovingRight = false;
	//		 break;
	//	 
	//	 default:
	//		 break;
	//	 }
	//	 break;
	// case SDL_KEYDOWN:
	//	 switch (e.key.keysym.sym) {
	//	 case SDLK_LEFT:
	//		 mMovingRight = false;
	//		 mMovingLeft = true;
	//		 break;
	//	 case SDLK_RIGHT:
	//		 mMovingLeft = false;
	//		 mMovingRight = true;
	//		 break;
	//	 case SDLK_UP:
	//		 Jump();
	//		 break;
	//	 default:
	//		 break;
	//	 }
	//	 break;
	// }
	 }
	
	
 void Character::AddGravity(float deltaTime) {
	 
	 mPosition.y += GRAVITY * deltaTime;
	 mCanJump = false;
 }

 void Character::MoveLeft(float deltaTime) {
	 mPosition.x = mPosition.x - deltaTime*100;
	 mFacingDirection = FACING_LEFT;

 }
 void Character::MoveRight(float deltaTime) {
	 mPosition.x = mPosition.x + deltaTime * 100;
	 mFacingDirection = FACING_RIGHT;

 }
 void Character::Jump() {
	 if (!mJumping && mCanJump) {
		 mJumpForce = INITIAL_JUMP_FORCE;
		 mJumping = true;
		 mCanJump = false;
	 }
 }

void  Character::SetPosition(Vector2D newPosition){
	mPosition = newPosition;
	

}
Vector2D Character::GetPosition() {
	return mPosition;
}
float Character::GetCollisionRadius() {
	return mCollisionRadius;
}
Rect2D Character::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
	
}
bool Character::IsJumping() {
	  return mJumping;
}
void Character::CancelJump() {
	mJumpForce = 0;
}
void Character::SetAlive(bool mIsAlive) {
	isAlive = mIsAlive;
}
bool Character::GetAlive() {
	return isAlive;
}