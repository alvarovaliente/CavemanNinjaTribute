#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <list>
#include "SDL/include/SDL.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_GROUND,
	COLLIDER_PLAYER,
	COLLIDER_PLAYER_CROUCH,
	COLLIDER_FOOT,
	COLLIDER_ENEMY,
	COLLIDER_MOVECAMERA,
	COLLIDER_STARTLEVEL,
	COLLIDER_STONEAXE,
	COLLIDER_MAX
	
};

using namespace std;
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

	bool addNewCollider(Collider* c);
	bool removeCollider(Collider* c);

	list<Collider*> colliding;
};

#endif