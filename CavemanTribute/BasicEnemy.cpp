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
	
	
	idle.frames.push_back({ 308, 466, 26, 45 });
	idle.frames.push_back({ 436, 466, 26, 45 });
	idle.speed = 0.1f;

	//RUNNING
	running.frames.push_back({42, 218, 33, 37});
	running.frames.push_back({ 174, 217, 27, 38 });
	running.frames.push_back({ 301, 218, 28, 37 });
	running.frames.push_back({ 429, 216, 28, 39 });
	running.speed = 0.2f;

	//WALKING
	walking.frames.push_back({ 52, 82, 32, 45 });
	walking.frames.push_back({ 177, 84, 35, 43 });
	walking.frames.push_back({ 309, 82, 31, 45 });
	walking.frames.push_back({ 434, 83, 34, 44 });
	walking.speed = 0.1f;

	//ATTACK
	attack.frames.push_back({ 53, 335, 33, 48 });
	attack.frames.push_back({ 181, 312, 28, 71 });
	attack.frames.push_back({ 278, 340, 54, 43 });
	attack.speed = 0.1f;

	//POST ATTACK
	postAttack.frames.push_back({ 52, 719, 25, 48 });
	postAttack.frames.push_back({ 182, 723, 23, 44 });
	postAttack.frames.push_back({ 310, 719, 23, 47 });
	postAttack.speed = 0.3f;

	//RUNNING
	runnigFast.frames.push_back({ 418, 720, 40, 47 });
	runnigFast.frames.push_back({ 546, 720, 42, 47 });
	runnigFast.frames.push_back({ 674, 720, 41, 47 });
	runnigFast.frames.push_back({ 802, 720, 42, 42 });
	runnigFast.frames.push_back({ 930, 720, 40, 46 });
	running.speed = 0.2f;
}

BasicEnemy::~BasicEnemy()
{

}

bool BasicEnemy::Start()
{
	graphicsEnemy = App->Ftextures->Load("Sprites/enemy_caveman.png");
	graphicsPickUpFood = App->Ftextures->Load("Sprites/pickups_food.png");

	timeAnimationToIdle.start();

	return true;
}

update_status BasicEnemy::PreUpdate()
{
	
	
	if (status == ENEMY_IDLE)
	{
		if (timeAnimationInIdle.isStarted() && timeAnimationInIdle.getTicks() > 800)
		{
			status = ENEMY_WALKING;
			previousStatus = ENEMY_IDLE;
			speed.x = 0.4;
			timeAnimationInIdle.stop();
			timeAnimationToIdle.start();

		}
	}

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

			this->colliderBody->to_delete = true;
			this->colliderBody = App->FCollision->AddCollider({ this->position.x - 15, this->position.y, ENEMY_COLLIDER_BODY_WIDTH_RUNNING, ENEMY_COLLIDER_BODY_HEIGHT_RUNNING }, COLLIDER_ENEMY, this);

		}

		if (timeAnimationToIdle.isStarted() && timeAnimationToIdle.getTicks() > 2000)
		{
			status = ENEMY_IDLE;
			previousStatus = ENEMY_WALKING;
			speed.x = 0;
			timeAnimationInIdle.start();
			timeAnimationToIdle.stop();

			
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
		if (timeAnimationAttack.isStarted() && timeAnimationAttack.getTicks() > 500)
		{
			status = ENEMY_POSTATTACK;
			previousStatus = ENEMY_ATTACK;
			timeAnimationpostAttack.start();

			this->colliderBody->to_delete = true;
			this->colliderBody = App->FCollision->AddCollider({ this->position.x - 15, this->position.y, ENEMY_COLLIDER_BODY_WIDTH_WALKING, ENEMY_COLLIDER_BODY_HEIGHT_WALKING }, COLLIDER_ENEMY, this);
		}

	}

	if (status == ENEMY_POSTATTACK)
	{
		if (timeAnimationpostAttack.isStarted() && timeAnimationpostAttack.getTicks() > 800)
		{
			status = ENEMY_RUNNINGFAST;
			previousStatus = ENEMY_POSTATTACK;
			facingLeft = !facingLeft;
			timeAnimationRunningFast.start();
			speed.x = 2;
		}


	}

	if (status == ENEMY_RUNNINGFAST)
	{
		if (facingLeft)
		{
			position.x -= speed.x;
		}
		else
		{
			position.x += speed.x;
		}

		if (timeAnimationRunningFast.isStarted() && timeAnimationRunningFast.getTicks() > 3000)
		{
			status = ENEMY_WALKING;
			previousStatus = ENEMY_RUNNINGFAST;
			speed.x = 0.4;
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
				this->colliderBody = App->FCollision->AddCollider({ this->position.x - 15, this->position.y, ENEMY_COLLIDER_BODY_WIDTH_WALKING - 15, PLAYER_CROUCH_COLLIDER_BODY_HEIGHT }, COLLIDER_ENEMY, this);
				App->renderer->Blit(graphicsEnemy, position.x - 15, position.y, &(attack.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsEnemy, position.x, position.y, &(attack.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}

			
		}
		else
		{
			if (attack.getActualFrameNumber() == 1)
			{
				App->renderer->Blit(graphicsEnemy, position.x, position.y - 25, &(attack.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
			}
			else if (attack.getActualFrameNumber() == 2)
			{
				this->colliderBody->to_delete = true;
				this->colliderBody = App->FCollision->AddCollider({ this->position.x - 15, this->position.y, ENEMY_COLLIDER_BODY_WIDTH_WALKING - 15, PLAYER_CROUCH_COLLIDER_BODY_HEIGHT }, COLLIDER_ENEMY, this);

				App->renderer->Blit(graphicsEnemy, position.x - 15, position.y, &(attack.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsEnemy, position.x, position.y, &(attack.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
			}
		}
		break;

	case ENEMY_POSTATTACK:
		if (facingLeft)
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(postAttack.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
		}
		else
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(postAttack.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
		}
		break;

	case ENEMY_RUNNINGFAST:
		if (facingLeft)
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(runnigFast.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
		}
		else
		{
			App->renderer->Blit(graphicsEnemy, position.x, position.y, &(runnigFast.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
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

	case COLLIDER_STONEAXE:
	{
		infoParticle inf;
		inf.position.x = this->position.x;
		inf.position.y = this->position.y + 20;
		inf.text = this->graphicsPickUpFood;
		App->FParticle->createParticle(inf, PARTICLE_PICKUPFOOD, COLLIDER_PICKUPFOOD);

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