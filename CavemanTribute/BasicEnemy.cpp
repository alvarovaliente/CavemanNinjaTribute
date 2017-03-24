#include "BasicEnemy.h"
#include "Application.h"
#include "MTextures.h"
#include "MRender.h"
#include "MInput.h"
#include "MCollision.h"
#include "MParticle.h"
#include "Particle.h"
#include "MScene.h"
#include <time.h>
#include <stdlib.h>


using namespace std;

BasicEnemy::BasicEnemy(infoGameObject info)
{
	type = BASIC_ENEMY;
	position = info.position;
	status = ENEMY_WALKING;
	facingLeft = true;
	speed.x = 0.4;
	//IDLE
	//idle.frames.push_back({ 52, 462, 32, 49});
	//idle.frames.push_back({ 180, 466, 32, 45 });
	idle.frames.push_back({ 308, 466, 26, 45 });
	//idle.frames.push_back({ 436, 466, 26, 45 });
	idle.speed = 0.1f;

	//RUNNING
	running.frames.push_back({42, 218, 33, 37});
	running.frames.push_back({ 174, 217, 27, 38 });
	running.frames.push_back({ 301, 218, 28, 37 });
	running.frames.push_back({ 429, 216, 28, 39 });
	running.speed = 0.2f;

	walking.frames.push_back({ 52, 82, 32, 45 });
	walking.frames.push_back({ 177, 84, 35, 43 });
	walking.frames.push_back({ 309, 82, 31, 45 });
	walking.frames.push_back({ 434, 83, 34, 44 });
	walking.speed = 0.1f;

	attack.frames.push_back({ 53, 335, 33, 48 });
	attack.frames.push_back({ 181, 312, 28, 71 });
	attack.frames.push_back({ 278, 340, 54, 43 });
	attack.speed = 0.1f;
}

BasicEnemy::~BasicEnemy()
{

}

bool BasicEnemy::Start()
{
	graphicsEnemy = App->Ftextures->Load("Sprites/enemy_caveman.png");


	return true;
}

update_status BasicEnemy::PreUpdate()
{
	
	
	//LOG("Distance: %f", (App->FGameObject->returnPlayer()->position.x - position.x));

	if (status == ENEMY_WALKING){

		if (facingLeft)
		{
			position.x -= speed.x;
		}
		else
		{
			position.x += speed.x;
		}

		if (App->FGameObject->returnPlayer()->position.x - position.x > -80)
		{
			status = ENEMY_RUNNING;
			previousStatus = ENEMY_WALKING;
			speed.x = 1;
			position.y += 5;

		}



	}

	if (status == ENEMY_RUNNING){

		if (facingLeft)
		{
			position.x -= speed.x;
		}
		else
		{
			position.x += speed.x;
		}


		if (App->FGameObject->returnPlayer()->position.x - position.x > -30)
		{
			status = ENEMY_ATTACK;
			previousStatus = ENEMY_RUNNING;
			speed.x = 0;
			position.y -= 5;
			timeAnimationAttack.start();

		}
		
	}

	if (status == ENEMY_ATTACK)
	{
		if (timeAnimationAttack.isStarted() && timeAnimationAttack.getTicks() > 420)
		{
			status = ENEMY_RUNNING;
			previousStatus = ENEMY_ATTACK;
			speed.x = 1;
			position.y += 5;
			facingLeft = !facingLeft;
		}

	}

	return UPDATE_CONTINUE;

}

update_status BasicEnemy::Update()
{
	
	colliderBody->SetPos(position.x, position.y);

	//drawing
	switch (status)
	{
	case ENEMY_IDLE:
		if (facingLeft)
		{ 
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(idle.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
		}
		else
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(idle.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
		}
		break;

	case ENEMY_WALKING:
		if (facingLeft)
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(walking.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
		}
		else
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(walking.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
		}
		break;

	case ENEMY_RUNNING:
		if (facingLeft)
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(running.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
		}
		else
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(running.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
		}
		break;

	case ENEMY_ATTACK:
		if (facingLeft)
		{
			if (attack.getActualFrameNumber() == 1)
			{
				App->renderer->Blit(graphicsEnemy, position.x, position.y-25, &(attack.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else if (attack.getActualFrameNumber() == 2)
			{
				this->colliderBody->to_delete = true;
				this->colliderBody = App->FCollision->AddCollider({ this->position.x - 15, this->position.y, ENEMY_COLLIDER_BODY_WIDTH - 15, PLAYER_CROUCH_COLLIDER_BODY_HEIGHT }, COLLIDER_ENEMY, this);
				App->renderer->Blit(graphicsEnemy, position.x - 15, position.y, &(attack.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsEnemy, position.x, position.y, &(attack.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}

			
		}
		else
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(attack.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
		}
		break;

	default:
		break;
	}

	return UPDATE_CONTINUE;
}

bool BasicEnemy::CleanUp()
{
	App->Ftextures->Unload(graphicsEnemy);
	
	return true;
}

bool const BasicEnemy::isDead()
{
	return dead;
}

void BasicEnemy::die()
{

}

void BasicEnemy::OnCollision(Collider* c1, Collider* c2)
{
	
}

void BasicEnemy::OnCollisionEnter(Collider* c1, Collider* c2)
{
	switch (c2->type)
	{


	case COLLIDER_PLAYER:
	{
		//facingLeft = !facingLeft;
	}
	break;

	case COLLIDER_STONEAXE:
	{
		dead = true;
		colliderBody->to_delete = true;
	}
	break;

	default:
		break;

	}
}

void BasicEnemy::OnCollisionExit(Collider* c1, Collider* c2)
{

}