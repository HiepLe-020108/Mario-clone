#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Commons.h"
using namespace::std;

	
	Texture2D::Texture2D(SDL_Renderer* renderer) {
		mRenderer = renderer;
		mTexture = NULL;

		mWidth = 0;
		mHeight = 0;
	}
	Texture2D::~Texture2D() {
		Free();

		mRenderer = NULL;
	}

	bool Texture2D::LoadFromFile(string path)
	{
		Free();

		std::cout << path;
	
		SDL_Surface* pSurface = IMG_Load(path.c_str());
		if (pSurface != NULL)
		{
			SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xff, 0xff));
			mWidth = pSurface->w;
			mHeight = pSurface->h;

			mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
			if (mTexture == NULL)
			{
				cout << "Unable to create texture from surface. Error:" << SDL_GetError() << endl;
			}

			SDL_FreeSurface(pSurface);
		}
		
		else {
			cout << "Unable to create texture from surface. Error:" << IMG_GetError() << endl;
		}
		return mTexture != NULL;
	}
	void Texture2D::Free(){
		if (mTexture != NULL){
			SDL_DestroyTexture(mTexture);
			mTexture = NULL;
			}
			mWidth = 0;
			mHeight = 0;
	}
	
	void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle ){
		//SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0x00);
		
		SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };
		SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);
			//SDL_RenderClear(mRenderer);
			//SDL_RenderPresent(mRenderer);
		
	}
	void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
	{
		SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
	}
	

	
	

	
 