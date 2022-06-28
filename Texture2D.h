#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H
#include "Commons.h"
#include <SDL.h>
#include <iostream>
#include <string>
using std::string;
class Texture2D {
public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(string path);
	void Free();

	void Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
	
 };
#endif //_TEXTURE2D_H