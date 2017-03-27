#include "Globals.h"
#include "Particle.h"
#include "Application.h"
#include "MRender.h"
#include "MCollision.h"
#include "PickUpFood.h"


PickUpFood::PickUpFood(infoParticle info, TYPEFOOD typeF) : Particle(info)
{
	type = typeF;
	position.x = info.position.x;
	position.y = info.position.y;
	texture = info.text;

	//APPLE
	apple.frames.push_back({ 9, 16, 13, 15 });
	apple.speed = 0.1f;
	lifeRestore = 3;
	lifetime = 4000;

	timeAlive.start();
}

PickUpFood::~PickUpFood()
{

}


bool PickUpFood::Start()
{
	
	return true;
}

update_status PickUpFood::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}

update_status PickUpFood::Update()
{


	if (timeAlive.isStarted() && timeAlive.getTicks() > lifetime)
	{
	die();
	}

	switch (type)
	{

	case APPLE:
		App->renderer->Blit(texture, position.x, position.y, &(apple.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
		break;

	default:
		break;
	}

	return UPDATE_CONTINUE;
	
}

void PickUpFood::OnCollisionEnter(Collider* c1, Collider* c2)
{

}


void PickUpFood::OnCollision(Collider* c1, Collider* c2)
{

}

void PickUpFood::OnCollisionExit(Collider* c1, Collider* c2)
{

}

void PickUpFood::die()
{
	dead = true;
	this->collider->to_delete = true;
}

bool const PickUpFood::isDead()
{
	return this->dead;
}