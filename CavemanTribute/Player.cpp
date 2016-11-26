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

	gravity = 2;

	facingRight = true;

	grounded = false;
	jumping = false;


	//Animations

	//idle
	idle.frames.push_back({ 50, 81, 27, 46 });
	idle.speed = 0.2f;

	//walking
	walking.frames.push_back({ 178, 83, 27, 44 });
	walking.frames.push_back({ 304, 80, 33, 47 });
	walking.frames.push_back({ 434, 83, 27, 44 });
	walking.frames.push_back({ 46, 208, 40, 47 });
	walking.speed = 0.12f;

	//crouch
	crouch.frames.push_back({ 180, 606, 30, 33 });
	crouch.speed = 0.2f;

	//lookup
	lookUp.frames.push_back({ 50, 594, 27, 45 });
	lookUp.speed = 0.2f;

	//jump
	jump.frames.push_back({ 178, 205, 31, 50 });
	jump.frames.push_back({ 178, 205, 31, 50 });
	jump.frames.push_back({ 301, 205, 38, 45 });
	jump.frames.push_back({ 301, 205, 38, 45 });
	jump.frames.push_back({ 301, 205, 38, 45 });
	jump.frames.push_back({ 434, 205, 27, 48 });
	jump.frames.push_back({ 434, 205, 27, 48 });
	jump.frames.push_back({ 434, 205, 27, 48 });
	jump.speed = 0.1f;

	//falling
	falling.frames.push_back({ 434, 205, 27, 48 });
	falling.speed = 0.1f;

	//double jump
	doubleJump.frames.push_back({ 52, 336, 24, 40 });
	doubleJump.frames.push_back({ 174, 338, 38, 38 });
	doubleJump.frames.push_back({ 306, 347, 34, 26 });
	doubleJump.frames.push_back({ 430, 342, 38, 38 });
	doubleJump.frames.push_back({ 53, 464, 24, 40 });
	doubleJump.frames.push_back({ 176, 464, 32, 41 });
	doubleJump.frames.push_back({ 300, 470, 35, 24 });
	doubleJump.frames.push_back({ 428, 464, 38, 38 });
	doubleJump.speed = 0.25f;

	//shoot
	shoot.frames.push_back({ 553, 81, 35, 46 });
	shoot.frames.push_back({ 691, 84, 40, 43 });
	shoot.speed = 0.1f;


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

				switch (status)
				{
				case PLAYER_IDLE:
					LOG("IDLE");
					break;
				case PLAYER_WALKING:
					LOG("WALKING");
					break;
				case PLAYER_CROUCH:
					LOG("CROUCH");
					break;
				case PLAYER_LOOKUP:
					LOG("LOOKUP");
					break;
				case PLAYER_JUMP:
					LOG("JUMP");
					break;
				case PLAYER_FALLING:
					LOG("FALLING");
					break;
				case PLAYER_DOUBLEJUMP:
					LOG("DOUBLE JUMP");
					break;
				default:
					break;
				}


				//NORMAL JUMP

				//if its almost in the top point doing up and down we reduce the gravity for an smooth effect
				if (status == PLAYER_JUMP && timeJump.isStarted() && timeJump.getTicks() >= 400)
				{
					gravity = GRAVITY_SMOOTH;
				
				}

				//its going up normal jump
				if (status == PLAYER_JUMP && timeJump.isStarted() && timeJump.getTicks() <= 500)
				{	
					position.y -= gravity;
					grounded = false;

					//if while are jumping we press the walking right button
					if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && status != PLAYER_CROUCH)
					{
						walkingRightF();
					}

					//if while are jumping we press the walking left button
					if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && status != PLAYER_CROUCH)
					{
						walkingLeftF();
					}


				}
				else if (status == PLAYER_JUMP && timeJump.isStarted() && timeJump.getTicks() >= 500)
				{
					status = PLAYER_FALLING;
					previousStatus = PLAYER_JUMP;
				}
		
				//DOUBLE JUMP

				//if its almost in the top point doing up and down we reduce the gravity for an smooth effect
				if (status == PLAYER_JUMP && timeJump.isStarted() && timeJump.getTicks() >= 400)
				{
					gravity = GRAVITY_SMOOTH;

				}

				//its going up double jump
				if (status == PLAYER_DOUBLEJUMP && timeDoubleJump.isStarted() && timeDoubleJump.getTicks() <= 500)
				{
					position.y -= gravity;
					grounded = false;

					//if while are double jumping we press the walking right button
					if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && status != PLAYER_CROUCH)
					{
						walkingRightF();
					}

					//if while are double jumping we press the walking left button
					if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && status != PLAYER_CROUCH)
					{
						walkingLeftF();
					}


				}
				else if (status == PLAYER_DOUBLEJUMP && timeDoubleJump.isStarted() && timeDoubleJump.getTicks() >= 500 && timeDoubleJump.getTicks() <= 700)
				{
					position.y += gravity;

					//if while are double jumping we press the walking right button
					if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && status != PLAYER_CROUCH)
					{
						walkingRightF();
					}

					//if while are double jumping we press the walking left button
					if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && status != PLAYER_CROUCH)
					{
						walkingLeftF();
					}
				}
				else if (status == PLAYER_DOUBLEJUMP && timeDoubleJump.isStarted() && timeDoubleJump.getTicks() >= 700)
				{
					status = PLAYER_FALLING;
					previousStatus = PLAYER_DOUBLEJUMP;
				}


				//FALLING

				if (status == PLAYER_FALLING || status == PLAYER_IDLE || status == PLAYER_SHOOT)
				{

					if (timeJump.getTicks() >= 600)
					{
						gravity = GRAVITY +0.5;
					}

					if (timeDoubleJump.getTicks() >= 700)
					{
						gravity = GRAVITY + 0.7;
					}

					if (!grounded){

						//if while are falling we press the walking right button
						if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && status != PLAYER_CROUCH)
						{
							walkingRightF();
						}

						//if while are falling we press the walking left button
						if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && status != PLAYER_CROUCH)
						{
							walkingLeftF();
						}

						position.y += gravity;
					}
				}

				//walking right
				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && status != PLAYER_CROUCH)
				{

					//DOUBLE JUMP inside walking right
					if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
					{
						if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN  && !jumping)
						{
							status = PLAYER_DOUBLEJUMP;
							previousStatus = PLAYER_LOOKUP;
							doubleJumpF();
						}
						else if (!jumping){
							status = PLAYER_WALKING;
							previousStatus = PLAYER_DOUBLEJUMP;
						
						}
					}


					//NORMAL JUMP inside walking right
					if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN  && !jumping)
					{
						status = PLAYER_JUMP;
						previousStatus = PLAYER_WALKING;
						jumpF();
					}
					else if (!jumping)
					{
						status = PLAYER_WALKING;
						previousStatus = PLAYER_JUMP;
						walkingRightF();
					}

				

				}
				

				//walking left
				if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && status != PLAYER_CROUCH)
				{
					//DOUBLE JUMP inside walking right
					if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
					{
						if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN  && !jumping)
						{
							status = PLAYER_DOUBLEJUMP;
							previousStatus = PLAYER_WALKING;
							doubleJumpF();
						}
						else if (!jumping){
							status = PLAYER_WALKING;
							previousStatus = PLAYER_DOUBLEJUMP;

						}
					}


					//NORMAL JUMP inside walking right
					if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN  && !jumping)
					{
						status = PLAYER_JUMP;
						previousStatus = PLAYER_WALKING;
						jumpF();
					}
					else if (!jumping)
					{
						status = PLAYER_WALKING;
						previousStatus = PLAYER_JUMP;
						walkingLeftF();
					}
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
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && status != PLAYER_JUMP && status != PLAYER_FALLING) 
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
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
				{
					if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN  && !jumping)
					{
						status = PLAYER_DOUBLEJUMP;
						previousStatus = PLAYER_LOOKUP;
						doubleJumpF();
					}
					else if (!jumping && status != PLAYER_WALKING){
						status = PLAYER_LOOKUP;
						previousStatus = PLAYER_DOUBLEJUMP;
					
					}
				}

				//look normal right
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && status == PLAYER_LOOKUP && facingRight == true)
				{
					status = PLAYER_IDLE;
					previousStatus = PLAYER_LOOKUP;
				}

				//look normal left
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && status == PLAYER_LOOKUP && facingRight == false)
				{			
					status = PLAYER_IDLE;
					previousStatus = PLAYER_LOOKUP;
				}

				//jump
				if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN  && !jumping && status != PLAYER_CROUCH)
				{
					status = PLAYER_JUMP;
					previousStatus = PLAYER_IDLE;
					jumpF();
				}

				//SHOOT
				if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
				{
					timeShoot.start();
					status = PLAYER_SHOOT;
					previousStatus = PLAYER_IDLE;
				}

				if (timeShoot.isStarted() && timeShoot.getTicks() >= 200)
				{
					status = PLAYER_IDLE;
					previousStatus = PLAYER_SHOOT;
					shoot.Reset();
					timeShoot.stop();
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

		case PLAYER_FALLING:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(falling.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(falling.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
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

		case PLAYER_JUMP:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(jump.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(jump.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
			}
		}

		break;

		case PLAYER_DOUBLEJUMP:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(doubleJump.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(doubleJump.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
			}
		}

		break;

		case PLAYER_SHOOT:
		{
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(shoot.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(shoot.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
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


update_status Player::jumpF()
{
	timeJump.start();
	position.y -= 15;
	jumping = true;
	grounded = false;
	gravity = GRAVITY;
	return UPDATE_CONTINUE;
}

update_status Player::doubleJumpF()
{
	timeDoubleJump.start();
	position.y -= 40;
	jumping = true;
	grounded = false;
	gravity = GRAVITY;
	return UPDATE_CONTINUE;
}



bool Player::CleanUp()
{
	App->Ftextures->Unload(graphicsPlayer);
	

	return true;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{

	switch (c2->type)
	{

	case COLLIDER_GROUND:
	{
		grounded = true;

		if (status == PLAYER_FALLING)
		{
			jump.Reset();
			status = PLAYER_IDLE;
			previousStatus = PLAYER_FALLING;
			jumping = false;
		}
		
	}
	break;

	default:

		break;
	}
}
