#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"
#include "Timer.h"
#include "Animation.h"

struct SDL_Texture;
class Collider;

enum PARTICLE_TYPE
{
	PARTICLE_SOFTSHOT = 1,
	PARTICLE_HARDSHOT
};


struct infoParticle
{
	fPoint position;
	fPoint speed;
	bool visible;
	bool dead;
	Uint32 lifetime;
	Animation anim;
	Animation explo;
	SDL_Texture* text;
};


class Particle
{


public:

	//variables
	fPoint position;
	fPoint speed;
	bool visible;
	bool dead;
	Timer time;
	Uint32 lifetime;
	Particle *link = nullptr;
	Collider *collider = nullptr;

	//methods
	Particle(infoParticle info);
	virtual ~Particle();

	virtual bool Start();
	virtual update_status Update();
	virtual const bool isDead();
	virtual void OnCollision(Collider* c1, Collider* c2);

};

#endif // __PARTICLE_H__