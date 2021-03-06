#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <string>
#include < iostream >
#include "GameScreenManager.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>
using namespace std;
//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
//Function Prototypes
bool InitSDL();
void CloseSDL();

bool Update();
bool quit = false;
void Render();
SDL_Texture* LoadTextureFromFile( string path );
void  FreeTexture();
void LoadMusic(string path);
float gocquay = 0;
Mix_Music* gMusic = NULL;
int main(int argc, char* args[])
{
	if (InitSDL()) {
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);
		LoadMusic("Music/Mario.ogg");
		gOldTime = SDL_GetTicks();
		while (!quit) {
			if (Mix_PlayingMusic() == 0) {
				Mix_PlayMusic(gMusic, -1);
			}
			Render();
			quit = Update();
		}
		
	}
	
	CloseSDL();

	return 0;
}
bool InitSDL() {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL did not initialise. Error : " << SDL_GetError();
		return false;
	}
	else {
		gWindow = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	}
	if (gWindow == NULL) {
		cout << "Window was not created. Error: "<< SDL_GetError();
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer != NULL) 
	{
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags)) {
			cout << "SDL_Image could not initiallise.Error :" << IMG_GetError();
			return false;
		}

		gTexture = LoadTextureFromFile("Images/test.bmp");
		if (gTexture == NULL) {
			return false;
		}
	}
	else {
		cout << "Renderer could not initiallise. Error:" << SDL_GetError();
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cout << "Mixer could not iniitialise error:  " << Mix_GetError();
		return false;
	}
	if (TTF_Init() < 0) {

		cout << "Error: " << SDL_GetError() << endl;

		return false;

	}
	return true;
}
void Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	 //SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
	// SDL_RenderCopyEx(gRenderer, gTexture, NULL, &renderLocation, gocquay, NULL, SDL_FLIP_NONE);
	gameScreenManager->Render();
	 
	SDL_RenderPresent(gRenderer);
	 
	  
	  
}


SDL_Texture* LoadTextureFromFile(string path)
	{
		FreeTexture();

		SDL_Texture* pTexture = NULL;

		SDL_Surface* pSurface = IMG_Load(path.c_str());
		if (pSurface != NULL)
		{
			pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
			if (pTexture == NULL)
			{
				cout << "Unable to create texture from surface. Error:" << SDL_GetError() << endl;
			}

			SDL_FreeSurface(pSurface);
		}

			else  {
				cout << "Unable to create texture from surface. Error:" << IMG_GetError() << endl;
			}
		return pTexture;
	}
	


void CloseSDL() {
	FreeTexture();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	IMG_Quit();
	SDL_Quit();
	delete gameScreenManager;
	gameScreenManager = NULL;
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	TTF_Quit();
}
bool Update() {
	Uint32 newTime = SDL_GetTicks();
	SDL_Event e;
	SDL_PollEvent(&e);
	
	switch (e.type) {
	case SDL_QUIT:
		return true;
		break;
	
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_RETURN:
			if (gameScreenManager->GetNextGameState() == GAME_STATE) {
				gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
				break;
			}
			else if (gameScreenManager->GetCurrentGameState() == GAME_STATE) {
				gameScreenManager->ChangeScreen(SCREEN_INTRO);
				break;
			}
			else if (gameScreenManager->GetNextGameState() == EXIT_STATE) {
				return true;
			}
			break;
		}

	}
	
	
	
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	//set curren time to be old time 
	gOldTime = newTime;
	return false;
}
void FreeTexture() {
	if (gTexture != NULL) {
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}
}

void LoadMusic(string path) {
	gMusic = Mix_LoadMUS(path.c_str());
	if (gMusic == NULL) {
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
	
}
