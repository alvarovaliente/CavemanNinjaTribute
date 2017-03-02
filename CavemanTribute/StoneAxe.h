#ifndef __STONEAXE_H__
#define __STONEAXE_H__


#include "Globals.h"
#include "Particle.h"
#include "Animation.h"

class Collider;

class StoneAxe : public Particle
{

public:

	//methods
	StoneAxe(infoParticle info);
	~StoneAxe();

	bool Start();
	update_status Update();
	bool const isDead();
	void OnCollision(Collider* c1, Collider* c2);
	void OnCollisionEnter(Collider* c1, Collider* c2);
	void OnCollisionExit(Collider* c1, Collider* c2);


	//animation
	Animation anim;
	Animation explosion;

	//graphics
	SDL_Texture *texture;

	//timers
	Timer timeToDie;
	Timer timeGoingUp;
	Timer timeGoingDown;

	int direction;


};

#endif // __SOFTSHOT_H__