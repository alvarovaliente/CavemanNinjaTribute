#include "Player.h"
#include "Application.h"
#include "MTextures.h"
#include "MRender.h"
#include "MInput.h"
#include "MCollision.h"
#include "MParticle.h"
#include "Particle.h"
#include "Timer.h"
#include "MScene.h"
#include "MAudio.h"

Player::Player()
{
	//Initialization
	this->type = PLAYER;

	position = position.SetToZero();
	
	speed.x = PLAYER_NORMAL_SPEED;
	speed.y = 0;

	status = PLAYER_IDLE;
	previousStatus = PLAYER_IDLE;

	actualLife = 18;

	facingRight = true;

	//Animations



}

Player::~Player()
{

}

bool Player::Start()
{
	graphicsPlayer = App->Ftextures->Load("player.png");

	for (int i = 0; i < 18; i++)
	{
		life.push_back(1);
	}

	for (int i = actualLife; i < 18; i++)
	{
		life[i] = 0;
	}

	return true;
}

update_status Player::PreUpdate()
{
	while (!App->scene->pause)
	{


		//Main state machine loop
		if (status != PLAYER_DYING)
		{


			//walking right
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				walkingRightF();
				
			}

			//walking left
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{

				walkingLeftF();
			}

			return UPDATE_CONTINUE;
		}



		return UPDATE_CONTINUE;

	}
}

update_status Player::Update()
{
	

		switch (status)
		{
		case PLAYER_IDLE:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(idleRight.GetCurrentFrame()), 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(idleLeft.GetCurrentFrame()), 1.0f);
			}
		}

		break;
		
		case PLAYER_WALKING:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(walkingRight.GetCurrentFrame()), 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(walkingLeft.GetCurrentFrame()), 1.0f);
			}
		}
		break;
		
		default:
			break;
		}

		return UPDATE_CONTINUE;

}

update_status Player::walkingRightF()
{
	position.x += speed.x;

	return UPDATE_CONTINUE;

}

update_status Player::walkingLeftF()
{
	position.x -= speed.x;

	return UPDATE_CONTINUE;

}


bool Player::CleanUp()
{
	App->Ftextures->Unload(graphicsPlayer);
	

	return true;
}
