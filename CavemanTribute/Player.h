#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameObject.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Globals.h"
#include "MGameObject.h"
#include "Timer.h"

enum PLAYER_STATUS
{
	PLAYER_IDLE_LEFT = 1,
	PLAYER_IDLE_RIGHT,

	PLAYER_WALKING_LEFT,
	PLAYER_WALKING_RIGHT,

	PLAYER_JUMPING_LEFT,
	PLAYER_JUMPING_RIGHT,

	PLAYER_RUNNING_LEFT,
	PLAYER_RUNNING_RIGHT,

	PLAYER_SHOOTING_LEFT,
	PLAYER_SHOOTING_RIGHT,

	PLAYER_FLYING,
	PLAYER_FALLING_LEFT,
	PLAYER_FALLING_RIGHT,

	PLAYER_PUSHING_LEFT,
	PLAYER_PUSHING_RIGHT,

	PLAYER_RUN_PUSHING_LEFT,
	PLAYER_RUN_PUSHING_RIGHT,

	PLAYER_SNOWBALL_LEFT,
	PLAYER_SNOWBALL_RIGHT,

	PLAYER_TRAPPED,

	PLAYER_REBORN,
	PLAYER_DYING


};

class Collider;

class Player : public GameObject
{
public:

	//Methods
	Player(infoGameObject inf);
	~Player();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void stopRolling();
	void fly();
	void OnCollision(Collider* c1, Collider* c2);

	//Textures
	SDL_Texture *graphicsPlayer = nullptr;
	SDL_Texture *graphicsEffectsPlayer = nullptr;
	SDL_Texture *graphicsSnowEffectPlayer = nullptr;

	//Animations
	Animation idleRight;
	Animation idleLeft;
	Animation walkingLeft;
	Animation walkingRight;
	Animation jumpingLeft;
	Animation jumpingRight;
	Animation runningLeft;
	Animation runningRight;
	Animation shootingLeft;
	Animation shootingRight;
	Animation flying;
	Animation fallingLeft;
	Animation fallingRight;
	Animation pushingLeft;
	Animation pushingRight;
	Animation snowballLeft;
	Animation snowballRight;
	Animation trapped;
	Animation dying;
	Animation snowAppear;
	Animation softShootLeft;
	Animation softShootRight;
	Animation hardShootLeft;
	Animation hardShootRight;
	Animation shootExplosion;

	//Timers
	Timer timeAnimationJump;
	Timer timeAnimationDying;
	Timer timeAnimationDyingButStillLives;
	Timer timeAnimationReborn;
	Timer timeAnimationFlying;
	Timer timeShooting;

	//Status
	PLAYER_STATUS status;
	PLAYER_STATUS previousStatus;

	//Control variables
	bool running;
	bool bigShoot;
	bool longShoot;
	bool godMode = false;
	int nLives;
	iPoint snowAppearOffset;
	iPoint speed;

	//Sounds
	unsigned int shotFx;
	unsigned int jumpFx;
	unsigned int pickObjectFx;
	unsigned int dieFx;
	

};


#endif // __PLAYER_H__