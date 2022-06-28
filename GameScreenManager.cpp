#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenMainMenu.h"
using namespace::std;
GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	mRenderer = renderer;
	mCurrentScreen  = NULL;
	ChangeScreen(startScreen);
}
GameScreenManager::~GameScreenManager() {
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render() {
	mCurrentScreen->Render();

}
void GameScreenManager:: Update(float deltaTime, SDL_Event e) {
	mCurrentScreen->Update(deltaTime, e);

}

void GameScreenManager::ChangeScreen(SCREENS newScreen) {
	//Clean up the old screen
	if (mCurrentScreen != NULL) {
		delete mCurrentScreen;
	}
	GameScreenLevel1* tempScreen;
	GameScreenMainMenu* menuScreen;
	switch (newScreen) {
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_MENU:
		menuScreen = new GameScreenMainMenu(mRenderer);
		mCurrentScreen = (GameScreen*)menuScreen;
		menuScreen = NULL;
		break;
	}
	
}
GAMESTATE GameScreenManager::GetCurrentGameState() {
	return mCurrentScreen->GetGameState();
}
GAMESTATE GameScreenManager::GetNextGameState() {
	return mCurrentScreen->GetNextGameState();
}
