#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameObject.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Globals.h"
#include "MGameObject.h"
#include "Timer.h"
#include "Module.h"

enum PLAYER_STATUS
{
	PLAYER_IDLE = 1,
	PLAYER_WALKING,
	PLAYER_JUMPING,
	PLAYER_SHOOTING,
	PLAYER_FALLING,
	PLAYER_DYING


};

class Collider;

class Player : public GameObject
{
public:

	//Methods
	Player();
	virtual ~Player();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	//Behaviour methods
	update_status walkingRightF();
	update_status walkingLeftF();

	//Textures
	SDL_Texture *graphicsPlayer = nullptr;

	//Animations
	Animation idleRight;
	Animation idleLeft;
	Animation walkingRight;
	Animation walkingLeft;

	//Status
	PLAYER_STATUS status;
	PLAYER_STATUS previousStatus;

	//Control variables
	bool godMode = false;
	bool facingRight;
	iPoint speed;
	vector <int> life;
	int actualLife;

};


#endif // __PLAYER_H__