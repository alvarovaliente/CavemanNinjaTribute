#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLATFORM,
	COLLIDER_PLATFORM_SPEC,
	COLLIDER_PLATFORM_BORDER_LEFT,
	COLLIDER_PLATFORM_BORDER_RIGHT,
	COLLIDER_PLATFORM_BORDER_LEFT_SPEC,
	COLLIDER_PLATFORM_BORDER_RIGHT_SPEC,
	COLLIDER_PLAYER,
	COLLIDER_FOOT,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SOFT_SHOT,
	COLLIDER_PLAYER_HARD_SHOT,
	COLLIDER_POTION_RED,
	COLLIDER_POTION_BLUE,
	COLLIDER_POTION_YELLOW,
	COLLIDER_MAX
};

class Module;


class Collider
{

public:
	SDL_Rect rect;
	bool to_delete;
	COLLIDER_TYPE type;
	Module* callback;
	bool active;
	bool launchable;
	bool rolling;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE typeof, Module* callbackM = nullptr);
	~Collider();

	void SetPos(float x, float y);

	bool const CheckCollision(SDL_Rect r) const;
};

#endif