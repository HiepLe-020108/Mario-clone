#include "CharacterKoopa.h"
#include "Character.h"


CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath,
	LevelMap* map, Vector2D startPosition, FACING startFacing,
   float movementSpeed) :
	Character(renderer, imagePath, startPosition,  map)
{
	mFacingDirection = startFacing;
	mMovementSpeed   = movementSpeed;
	mPosition        = startPosition;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterKoopa::~CharacterKoopa(){
}
void CharacterKoopa::TakeDamage() {
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();

}
void CharacterKoopa::Jump() {
	if (!mJumping && mCanJump) {
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}
void CharacterKoopa::FlipRightwayUp() {
	if (!mFacingDirection || mFacingDirection) {
		mFacingDirection = FACING_LEFT;
		mInjured = false;
	}
	Jump();
}
void CharacterKoopa::Render() {
	//var to hold the left position of the sprite we want to draw
	int left = 0.0f;
	// if injured move the left position to be the left position of the second image on the spritesheet

	if (mInjured)
	{
		left = mSingleSpriteWidth;
	}
	//get the portion of the pritesheet you want to draw
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	//detenibe where you want ti draw
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
	// then draw it facing the correct direction
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);

	}
	else {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
	
}
void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{ 

	Character::Update(deltaTime, e);
	if (!mInjured) {
		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft = true;
			mMovingRight = false;
			MoveLeft(deltaTime);
		}
		else if (mFacingDirection == FACING_RIGHT) {
			mMovingLeft = false;
			mMovingRight = true;
			MoveRight(deltaTime);
		}
		if (mPosition.x < 0) {
			mFacingDirection = FACING_RIGHT;
		}
		if (mPosition.x > 480) {
			mFacingDirection = FACING_LEFT;
		}
	}
	else {
		mMovingLeft = false;
		mMovingRight = false;
		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0.0) {
			FlipRightwayUp();
		}
	}
	
}
bool CharacterKoopa::GetInjured() {
	return mInjured;
}

