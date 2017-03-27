#include "Globals.h"
#include "Application.h"
#include "MRender.h"
#include "MParticle.h"
#include "SDL/include/SDL.h"
#include "Point.h"
#include "StoneAxe.h"
#include "PickUpFood.h"
#include "Particle.h"



MParticle::MParticle(){

}

MParticle::~MParticle()
{

}

bool MParticle::Start()
{

	for (auto& it : particles)
	{
		if (it != nullptr)
		{
			it->Start();
		}

	}


	return true;
}

update_status MParticle::Update()
{

	

	if (particles.size() > 0){
		for (auto& it : particles)
		{
			if (it != nullptr)
			{
				it->Update();
			}

		}
	}


	return UPDATE_CONTINUE;
}


update_status MParticle::PreUpdate()
{

	// Remove all colliders scheduled for delete
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end();)
	{
		if ((*it)->dead == true)
		{
			RELEASE(*it);
			it = particles.erase(it);
		}
		else
			++it;
	}
	return UPDATE_CONTINUE;
}

bool MParticle::CleanUp()
{
	

	for (list<Particle*>::reverse_iterator it = particles.rbegin(); it != particles.rend(); ++it)
		RELEASE(*it);

	particles.clear();

	return true;
}

void MParticle::OnCollision(Collider* c1, Collider* c2)
{
	for (auto& it : particles)
	{
		if (it != nullptr)
		{
			if ((it)->collider == c1)
			{
				it->OnCollision(c1, c2);
			}
		}
	}
}

void MParticle::OnCollisionEnter(Collider* c1, Collider* c2)
{
	for (auto& it : particles)
	{
		if (it != nullptr)
		{
			if ((it)->collider == c1)
			{
				it->OnCollisionEnter(c1, c2);
			}
		}
	}
}

void MParticle::OnCollisionExit(Collider* c1, Collider* c2)
{
	for (auto& it : particles)
	{
		if (it != nullptr)
		{
			if ((it)->collider == c1)
			{
				it->OnCollisionExit(c1, c2);
			}
		}
	}
}

void MParticle::createParticle(infoParticle info, PARTICLE_TYPE type, COLLIDER_TYPE collider_type)
{

	switch (type)
	{

	case PARTICLE_STONEAXE:
	{
		StoneAxe *axe = new StoneAxe(info);

		if (collider_type != COLLIDER_NONE)
		{
			axe->collider = App->FCollision->AddCollider({ axe->position.x, axe->position.y, 20, 20 }, collider_type, this);
		}

		particles.push_back(axe);
	}
	break;

	case PARTICLE_PICKUPFOOD:
	{
		PickUpFood *food = new PickUpFood(info,APPLE); //TO DO: random food
		

		if (collider_type != COLLIDER_NONE)
		{
			food->collider = App->FCollision->AddCollider({ food->position.x, food->position.y, PICKUPFOOD_COLLIDER_BODY_WIDTH, PICKUPFOOD_COLLIDER_BODY_WIDTH }, collider_type, this, dynamic_cast<Particle*>(food));
		}

		particles.push_back(food);
	}
	break;
	
	default:
		break;
	}



}
