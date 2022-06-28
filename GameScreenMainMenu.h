#pragma once
#ifndef _GAMESCREENMAINMENU_H
#define _GAMESCREENMAINMENU_H
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

class GameScreenMainMenu : GameScreen {

public:
	GameScreenMainMenu(SDL_Renderer* renderer);
	~GameScreenMainMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	
	float position1y;
	
protected:

private:

	bool SetUpLevelMenu();
	
	LevelMap* mLevelMap;
	

	
	float mBackgroundYPos;
	
	Texture2D* mTexture;
	Texture2D* mMario;
	TextRenderer* titleText;
	TextRenderer* levelText;
	TextRenderer* quitText;
};


#endif


