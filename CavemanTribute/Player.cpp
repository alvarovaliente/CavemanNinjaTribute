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

	
	speed.x = PLAYER_NORMAL_SPEED;
	speed.y = 0;

	status = PLAYER_IDLE;
	previousStatus = PLAYER_IDLE;

	actualLife = 18;

	facingRight = true;

	//Animations

	//idle
	idle.frames.push_back({ 50, 81, 27, 46 });
	idle.speed = 0.2f;

	//walking
	walking.frames.push_back({ 178, 83, 27, 44 });
	walking.frames.push_back({ 304, 80, 33, 47 });
	walking.frames.push_back({ 434, 83, 27, 44 });
	walking.frames.push_back({ 46, 208, 40, 47 });
	walking.speed = 0.1f;

	//crouch
	crouch.frames.push_back({ 180, 606, 30, 33 });
	crouch.speed = 0.2f;

	//lookup
	lookUp.frames.push_back({ 50, 594, 27, 45 });
	lookUp.speed = 0.2f;



}

Player::~Player()
{

}

bool Player::Start()
{
	graphicsPlayer = App->Ftextures->Load("Sprites/joe.png");

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
				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && status != PLAYER_CROUCH)
				{
					status = PLAYER_WALKING;
					previousStatus = PLAYER_IDLE;
					walkingRightF();

				}
				

				//walking left
				if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && status != PLAYER_CROUCH)
				{
					status = PLAYER_WALKING;
					previousStatus = PLAYER_IDLE;
					walkingLeftF();
				}

				//idle right
				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && status == PLAYER_WALKING && facingRight == true)
				{
					status = PLAYER_IDLE;
					previousStatus = PLAYER_WALKING;
				}

				//idle left
				if (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && status == PLAYER_WALKING && facingRight == false)
				{
					status = PLAYER_IDLE;
					previousStatus = PLAYER_WALKING;
				}

				//crouch
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
				{
					
					status = PLAYER_CROUCH;
					previousStatus = PLAYER_IDLE;
					crouchF();
				}

				//standUp right
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && status == PLAYER_CROUCH && facingRight == true)
				{
					standUpF();
					status = PLAYER_IDLE;
					previousStatus = PLAYER_CROUCH;
				}

				//standUp left
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && status == PLAYER_CROUCH && facingRight == false)
				{
					standUpF();
					status = PLAYER_IDLE;
					previousStatus = PLAYER_CROUCH;
				}

				//lookUp
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
				{
					status = PLAYER_LOOKUP;
					previousStatus = PLAYER_IDLE;
					lookUpF();
				}

				//look normal right
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && status == PLAYER_LOOKUP && facingRight == true)
				{
					lookNormalF();
					status = PLAYER_IDLE;
					previousStatus = PLAYER_LOOKUP;
				}

				//look normal left
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && status == PLAYER_LOOKUP && facingRight == false)
				{
					lookNormalF();
					status = PLAYER_IDLE;
					previousStatus = PLAYER_LOOKUP;
				}
				

				return UPDATE_CONTINUE;
			}



			return UPDATE_CONTINUE;
		}

}

update_status Player::Update()
{
		colliderBody->SetPos(position.x, position.y);
		
		
		switch (status)
		{
		case PLAYER_IDLE:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(idle.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(idle.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
			}
		}

		break;

		case PLAYER_WALKING:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(walking.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(walking.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
			}
		}
		break;

		case PLAYER_CROUCH:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(crouch.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(crouch.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
			}
		}

		break;

		case PLAYER_LOOKUP:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(lookUp.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(lookUp.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
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
	facingRight = true;
	
	return UPDATE_CONTINUE;
}

update_status Player::walkingLeftF()
{
	position.x -= speed.x;
	facingRight = false;
	
	return UPDATE_CONTINUE;
}


update_status Player::crouchF()
{
	speed.x = 0;
	position.y += 15;
	this->colliderBody->to_delete = true;
	this->colliderBody = App->FCollision->AddCollider({ this->position.x, this->position.y, PLAYER_COLLIDER_BODY_WIDTH, PLAYER_CROUCH_COLLIDER_BODY_HEIGHT }, COLLIDER_PLAYER, this);
	
	return UPDATE_CONTINUE;
}

update_status Player::standUpF()
{
	position.y -= 15;
	speed.x = PLAYER_NORMAL_SPEED;
	this->colliderBody->to_delete = true;
	this->colliderBody = App->FCollision->AddCollider({ this->position.x, this->position.y, PLAYER_COLLIDER_BODY_WIDTH, PLAYER_COLLIDER_BODY_HEIGHT }, COLLIDER_PLAYER, this);
	return UPDATE_CONTINUE;
}

update_status Player::lookUpF()
{

	position.y += 1;
	return UPDATE_CONTINUE;
}

update_status Player::lookNormalF()
{
	position.y -= 1;
	return UPDATE_CONTINUE;

}



bool Player::CleanUp()
{
	App->Ftextures->Unload(graphicsPlayer);
	

	return true;
}
