#ifndef __PICKUPFOOD_H__
#define __PICKUPFOOD_H__


#include "Globals.h"
#include "Application.h"
#include "Particle.h"
#include "Animation.h"
#include "MTextures.h"


enum TYPEFOOD
{
	APPLE = 0,
	STRAWBERRY,
	ORANGE,
	LEMON,
	WATERMELON,
	PEAR,


};

class PickUpFood : public Particle
{
public: 
	PickUpFood(infoParticle info, TYPEFOOD typeF);
	~PickUpFood();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool const isDead();
	void die();
	void OnCollision(Collider* c1, Collider* c2);
	void OnCollisionEnter(Collider* c1, Collider* c2);
	void OnCollisionExit(Collider* c1, Collider* c2);

	//graphics
	SDL_Texture *texture;

	//animation
	Animation apple;
	Animation strawberry;
	Animation orange;
	Animation lemon;
	Animation watermelon;
	Animation pear;

	int lifeRestore;
	int type;
	int lifetime;

	//timers
	Timer timeAlive;

};

#endif // __PICKUPFOOD_H__