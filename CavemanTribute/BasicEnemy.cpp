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

	//WALKING
	walking.frames.push_back({42, 218, 33, 37});
	walking.frames.push_back({ 174, 217, 27, 38 });
	walking.frames.push_back({ 301, 218, 28, 37 });
	walking.frames.push_back({ 429, 216, 28, 39 });
	walking.speed = 0.1f;
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
	
	if (status == ENEMY_WALKING){

		if (facingLeft)
		{
			position.x -= speed.x;
		}
		else
		{
			position.x += speed.x;
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
		facingLeft = !facingLeft;
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