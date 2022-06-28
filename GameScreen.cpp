#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer) {

	mRenderer = renderer;

}
GameScreen::~GameScreen() {

	mRenderer = NULL;

}

void GameScreen::Render() {

}
void GameScreen::Update(float deltaTime, SDL_Event e) {

}
 GAMESTATE GameScreen::GetGameState() {
	return currentState  ;
}
 GAMESTATE GameScreen::GetNextGameState() {
	return nextGameState;
}
 void GameScreen::SetGameState(GAMESTATE nowState) {
	 currentState = nowState;
 }
 void GameScreen::SetNextGameState(GAMESTATE andState) {
	 nextGameState = andState;
 }