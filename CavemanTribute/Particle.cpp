#include "Globals.h"
#include "Particle.h"
#include "Application.h"
#include "Point.h"

#include "Timer.h"



Particle::Particle(infoParticle info)
{
	position = info.position;
	speed = info.speed;
	visible = info.visible;
	dead = false;
	lifetime = info.lifetime;
}

Particle::~Particle()
{

}

bool Particle::Start()
{
	return true;
}


update_status Particle::Update()
{
	return UPDATE_CONTINUE;
}

bool const Particle::isDead()
{
	return dead;
}

void Particle::OnCollision(Collider* c1, Collider* c2)
{

}
