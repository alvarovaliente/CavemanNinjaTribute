#ifndef __MPARTICLE_H__
#define __MPARTICLE_H__

#include "Module.h"
#include "Globals.h"
#include "MCollision.h"
#include "Particle.h"
#include <list>

class MParticle : public Module
{
public:

	MParticle();
	~MParticle();

	bool Start();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();
	void createParticle(infoParticle info, PARTICLE_TYPE type, COLLIDER_TYPE collider_type);
	void OnCollision(Collider* c1, Collider* c2);


private:
	std::list<Particle*> particles;


};

#endif // __MPARTICLE_H__