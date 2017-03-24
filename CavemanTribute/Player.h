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
	PLAYER_CROUCH,
	PLAYER_LOOKUP,
	PLAYER_JUMP,
	PLAYER_FALLING,
	PLAYER_DYING,
	PLAYER_DOUBLEJUMP,
	PLAYER_SHOOT,
	PLAYER_SHOOTLOOKUP,
	PLAYER_SHOOTCROUCH


};

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
	void OnCollision(Collider* c1, Collider* c2);
	void OnCollisionEnter(Collider* c1, Collider* c2);
	void OnCollisionExit(Collider* c1, Collider* c2);

	//Behaviour methods
	update_status walkingRightF();
	update_status walkingLeftF();
	update_status crouchF();
	update_status standUpF();

	update_status jumpF();
	update_status doubleJumpF();
	update_status shootLookUpF();
	update_status endShootLookUpF();


	//Textures
	SDL_Texture *graphicsPlayer = nullptr;
	SDL_Texture *graphicsStoneAxe = nullptr;

	//Animations
	Animation idle;
	Animation walking;
	Animation crouch;
	Animation lookUp;
	Animation jump;
	Animation doubleJump;
	Animation falling;
	Animation shoot;
	Animation shootLookUp;
	Animation shootCrouch;

	Animation stoneAxe;

	//Status
	PLAYER_STATUS status;
	PLAYER_STATUS previousStatus;

	//Control variables
	bool godMode = false;
	bool facingRight;
	iPoint speed;
	vector <int> life;
	int actualLife;
	int gravity;
	bool grounded;
	bool jumping;
	bool hitted;
	

	//timers
	Timer timeJump;
	Timer timeDoubleJump;
	Timer timeShoot;
	Timer timeShootCrouch;
	Timer timeShootLookUp;
	Timer timeHitted;
};


#endif // __PLAYER_H__