#pragma once
#ifndef _COMMONS_H
#define _COMMONS_H
struct Vector2D
{
	float x;
	float y;

	Vector2D() {

		x = 0.0f;
		y = 0.0f;

	}

	Vector2D(float a, float b) {
		x = a;
		y = b;
	}
};
struct Rect2D {
	float x;
	float y;
	float width;
	float height;
	Rect2D() {
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;

	}
	Rect2D(float a, float b, float c, float d) {
		x = a;
		y = b;
		width = c;
		height = d;
	}
};
enum SCREENS {
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};
enum FACING {
	FACING_LEFT = 0,
	FACING_RIGHT
};
enum GAMESTATE {

	EXIT_STATE = 0,

	INTRO_STATE,

	GAME_STATE

};
#endif
