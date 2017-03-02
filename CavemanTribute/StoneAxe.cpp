
#include "StoneAxe.h"
#include "Globals.h"
#include "Particle.h"
#include "Application.h"
#include "MRender.h"
#include "MCollision.h"


StoneAxe::StoneAxe(infoParticle info) : Particle(info)
{
	anim = info.anim;
	explosion = info.explo;
	texture = info.text;
	time.start();
	speed.x = info.speed.x;
	speed.y = info.speed.y;
	lifetime = 4000;
	direction = info.direction;
	timeGoingUp.start();
}

StoneAxe::~StoneAxe()
{

}

bool StoneAxe::Start()
{

	return true;
}

update_status StoneAxe::Update()
{



	if (time.getTicks() >= lifetime)
	{
		

		dead = true;
		collider->to_delete = true;
	}



	if (!dead)
	{
		
		collider->SetPos(position.x, position.y);

		if (direction == SHOOTUP)
		{

			if (timeGoingUp.isStarted() && timeGoingUp.getTicks() <= 300)
			{
				LOG("UP");
				position.x += 0;
				position.y -= speed.y;
			}
		
		}
		else
		{
			if (timeGoingUp.isStarted() && timeGoingUp.getTicks() <= 200)
			{
				if (direction == SHOOTRIGHT){
					LOG("RIGHT");
					position.x += speed.x;
					position.y -= speed.y;
				}
				else if (direction == SHOOTLEFT)
				{
					LOG("LEFT");
					position.x -= speed.x;
					position.y -= speed.y;

				}
				
			}
		}

		
		if (direction == SHOOTUP)
		{
			if (timeGoingUp.isStarted() && timeGoingUp.getTicks() >= 300)
			{
				timeGoingUp.stop();
				timeGoingDown.start();
			}
		}
		else{

			if (timeGoingUp.isStarted() && timeGoingUp.getTicks() >= 200)
			{
				timeGoingUp.stop();
				timeGoingDown.start();
			}
		}

		if (timeGoingDown.isStarted())
		{
			if (direction == SHOOTRIGHT){
				position.x += speed.x;
				position.y += speed.y + 2.0f;
			}
			else if (direction == SHOOTLEFT)
			{
				position.x -= speed.x;
				position.y += speed.y + 2.0f;
			}
			else if (direction == SHOOTUP)
			{
				position.x += 0;
				position.y += speed.y;

			}
		}

	

		App->renderer->Blit(texture, position.x, position.y, &(anim.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);


	}

	return UPDATE_CONTINUE;
}

bool const StoneAxe::isDead()
{
	return this->dead;
}

void StoneAxe::OnCollision(Collider* c1, Collider* c2)
{

}

void StoneAxe::OnCollisionEnter(Collider* c1, Collider* c2)
{
	switch (c2->type)
	{
	case COLLIDER_GROUND:
	{
		
		dead = true;
		collider->to_delete = true;
		//timeToDie.start();
	}

	case COLLIDER_ENEMY:
	{
		

		//timeToDie.start();
		dead = true;
		collider->to_delete = true;
	}
	break;
	default:
		break;
	}
}

void StoneAxe::OnCollisionExit(Collider* c1, Collider* c2)
{

}
