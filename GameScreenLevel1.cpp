#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Commons.h"
#include "Collisions.h"
#include "Character.h"
#include "PowBlock.h"
#include <Windows.h>
using namespace::std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
	// mLevelMap = NULL;
}

GameScreenLevel1::~GameScreenLevel1() {
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete myCharacterMario;
	myCharacterMario = NULL;
	delete myCharacterMario;
	myCharacterLuigi = NULL;
	delete mPowBlock;
	mPowBlock = NULL;
	mEnemies.clear();
}

void GameScreenLevel1::Render() {
	
	mBackgroundTexture -> Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	myCharacterMario->Render(); //Vector2D(), SDL_FLIP_NONE
	myCharacterLuigi->Render(); //Vector2D(), SDL_FLIP_NONE
	

	for (unsigned int i = 0; i < mEnemies.size(); i++) {

		mEnemies[i]->Render();
		//koopaCharacter->Render();
		
		
	}
	mPowBlock->Render();
	// titleText->Render(mRenderer, "MARIO GAME!", SCREEN_WIDTH / 4 - 50, SCREEN_HEIGHT / 4);
}


void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		if (mScreenshakeTime <= 0.0f) {
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}
	myCharacterMario->Update(deltaTime, e);
	myCharacterLuigi->Update(deltaTime, e);
	
	if (Collisions::Instance()->Circle(myCharacterMario, myCharacterLuigi)) {
		
	}
	if (Collisions::Instance()->Box(myCharacterMario->GetCollisionBox(), myCharacterLuigi->GetCollisionBox())) {
		
	}
	UpdatePowBlock();
	
	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);
	createKoopaTimer -= deltaTime;
	if (createKoopaTimer <= 0) {
		createKoopaTimer = 5000;
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	}
}

bool GameScreenLevel1::SetUpLevel() {
	
	
	// titleText = new TextRenderer(50);

	SetLevelMap();
	
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;
	//Load the background texture 
	mBackgroundTexture = new Texture2D(mRenderer);
	 if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		std::cout << "Failed to load background texture!";
		return false;
	}
	 
	 myCharacterMario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(60, 340), mLevelMap);
	 myCharacterLuigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(180, 340), mLevelMap);
	 CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	 CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	return true;
}
void GameScreenLevel1::SetLevelMap() {
	int map[MAP_HEIGHT][ MAP_WIDTH ] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
									   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
	//Clear up any old map
	if (mLevelMap != NULL) {
		delete mLevelMap;
	}
	//set the new one
	mLevelMap = new LevelMap(map);
	
}

void  GameScreenLevel1::DoScreenshake() {
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}


void GameScreenLevel1::UpdatePowBlock() {
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), myCharacterMario->GetCollisionBox())) {
		if (mPowBlock != NULL ) {
			if (myCharacterMario->IsJumping()) {
				DoScreenshake();
				mPowBlock->TakeAHit();
				myCharacterMario->CancelJump();
			}
		}
	}
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), myCharacterLuigi->GetCollisionBox())) {
		if (mPowBlock != NULL) {
			if (myCharacterLuigi->IsJumping()) {
				DoScreenshake();
				mPowBlock->TakeAHit();
				myCharacterLuigi->CancelJump();
			}
		}
	}
	

}






void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e) {
	if (!mEnemies.empty()) 
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++) 
		{
			if (mEnemies[i]->GetPosition().y > 300.0f) 
			{
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies
					[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.5f)){
					mEnemies[i]->SetAlive(false);
				}
					
			}
			mEnemies[i]->Update(deltaTime, e);
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i] -> GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)) 
			{
				//Ignore the collosions if the enemy is behind a pipe?
			}
			else
			{
				if (Collisions::Instance()->Circle(mEnemies[i], myCharacterMario)&& mEnemies[i]->GetInjured() == false){}
					/*myCharacterMario->SetState(CHARACTER_STATE_PLAYER_DEATH);*/
				else if (Collisions::Instance()->Circle(mEnemies[i], myCharacterMario) && mEnemies[i]->GetInjured() == true) {
					mEnemies[i]->SetAlive(false);
					
				}
			}
			if (mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}


		if (enemyIndexToDelete != -1)
		{
			delete mEnemies[enemyIndexToDelete];
			mEnemies[enemyIndexToDelete] = NULL;
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);

		}
	}
}
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{

	koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, speed);
	mEnemies.push_back(koopaCharacter);
}

