#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "LevelMap.h"

#include <vector>
#include "TextRenderer.h"
#include <SDL_ttf.h>
class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel1 : GameScreen {
	
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePowBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	
protected:

private:
	
	bool SetUpLevel();
	CharacterMario* myCharacterMario;
	CharacterLuigi* myCharacterLuigi;
	CharacterKoopa* koopaCharacter;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	void SetLevelMap();
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	int createKoopaTimer = 5000;
	std::vector<CharacterKoopa* > mEnemies;
	void DoScreenshake();
	Texture2D* mBackgroundTexture;
	TextRenderer* titleText;
};


#endif