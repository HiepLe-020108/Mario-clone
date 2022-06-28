#include "GameScreenMainMenu.h"
#include <iostream>
#include "Texture2D.h"
using namespace std;

GameScreenMainMenu::GameScreenMainMenu(SDL_Renderer* renderer) : GameScreen(renderer) {
	
	SetUpLevelMenu();

	position1y = 200;
	
	
}
GameScreenMainMenu::~GameScreenMainMenu() {
	delete mTexture;
	mTexture = NULL;

}
void GameScreenMainMenu::Render() {
	
	titleText->Render(mRenderer, "MARIO GAME!", SCREEN_WIDTH / 4 - 50, SCREEN_HEIGHT / 4);
	levelText->Render(mRenderer, "Level 1", SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2);
	quitText->Render(mRenderer, "Quit", SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 1.4);
	mMario->Render(Vector2D(100, position1y), SDL_FLIP_NONE);

}
void GameScreenMainMenu::Update(float deltaTime, SDL_Event e) {
	switch (e.type)
	{

	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_DOWN:
			position1y = 300;
			SetNextGameState(EXIT_STATE);
			break;
		case SDLK_UP:
			position1y = 200;
			SetNextGameState(GAME_STATE);
			break;
		}
	}

}
bool GameScreenMainMenu::SetUpLevelMenu() {
	
	mMario = new Texture2D(mRenderer);
	if (!mMario->LoadFromFile("Images/Mario.png")) {
		cout << "Failed to load image" << endl;
		return false;
	}


	titleText = new TextRenderer(50);
	levelText = new TextRenderer(30);
	quitText = new TextRenderer(30);

	
	
	
	return true;
}
