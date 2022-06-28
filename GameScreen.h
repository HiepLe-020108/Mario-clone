#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H
#include <SDL.H>
#include "Commons.h"

class  GameScreen {
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	bool InitSDL();
	GAMESTATE GetGameState();
	GAMESTATE GetNextGameState();
	
protected:
	SDL_Renderer* mRenderer;
	GAMESTATE currentState;
	GAMESTATE nextGameState;
	void SetGameState(GAMESTATE nowState);
	void SetNextGameState(GAMESTATE andState);



};
#endif