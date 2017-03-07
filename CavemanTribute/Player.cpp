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

	status = PLAYER_FALLING;
	previousStatus = PLAYER_FALLING;

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
	lookUp.frames.push_back({ 50, 593, 27, 46 });
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
	shoot.frames.push_back({ 553, 81, 35, 46 });
	shoot.speed = 0.1f;

	//shoot look up
	shootLookUp.frames.push_back({ 552, 594, 47, 45 });
	shootLookUp.frames.push_back({ 692, 583, 27, 56 });
	shootLookUp.frames.push_back({ 552, 594, 47, 45 });

	shootLookUp.speed = 0.1f;


	//shoot crouch
	shootCrouch.frames.push_back({ 304, 606, 34, 33 });
	shootCrouch.frames.push_back({ 304, 606, 34, 33 });

	shootCrouch.frames.push_back({ 436, 606, 35, 33 });
	shootCrouch.frames.push_back({ 436, 606, 35, 33 });
	shootCrouch.frames.push_back({ 436, 606, 35, 33 });
	shootCrouch.frames.push_back({ 436, 606, 35, 33 });

	shootCrouch.frames.push_back({ 304, 606, 34, 33 });
	shootCrouch.frames.push_back({ 304, 606, 34, 33 });
	shootCrouch.speed = 0.3f;

	//stoneAxe
	stoneAxe.frames.push_back({ 8, 6, 21, 17 });
	stoneAxe.frames.push_back({ 42, 5, 17, 21 });
	stoneAxe.frames.push_back({ 74, 6, 15, 23 });
	stoneAxe.frames.push_back({ 102, 9, 19, 18 });
	stoneAxe.frames.push_back({ 4, 41, 21, 17 });
	stoneAxe.frames.push_back({ 37, 38, 17, 21 });
	stoneAxe.frames.push_back({ 71, 35, 15, 23 });
	stoneAxe.frames.push_back({ 103, 37, 19, 18 });
	jump.speed = 0.01f;
}

Player::~Player()
{

}

bool Player::Start()
{
	graphicsPlayer = App->Ftextures->Load("Sprites/joe.png");
	graphicsStoneAxe = App->Ftextures->Load("Sprites/weapon_tomahawk.png");

	for (int i = 0; i < 18; i++)
	{
		life.push_back(1);
	}

	for (int i = actualLife; i < 18; i++)
	{
		life[i] = 0;
	}

	timeJump.stop();
	timeDoubleJump.stop();
	timeShoot.stop();

	return true;
}

update_status Player::PreUpdate()
{
	while (!App->scene->pause)
	{
		
			
			//Main state machine loop
			if (status != PLAYER_DYING)
			{

				if (status == PLAYER_IDLE)
				{

					//SHOOT
					if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && status != PLAYER_CROUCH && status != PLAYER_LOOKUP && status != PLAYER_SHOOT && status != PLAYER_SHOOTCROUCH && status != PLAYER_SHOOTLOOKUP)
					{
						infoParticle inf;

						inf.anim = this->stoneAxe;
						inf.text = this->graphicsStoneAxe;
						inf.position.x = this->position.x;
						inf.position.y = this->position.y;
						inf.speed.x = 2.0;
						inf.speed.y = 0.4;
						if (facingRight)
						{
							inf.direction = SHOOTRIGHT;
						}
						else
						{
							inf.direction = SHOOTLEFT;
						}

						App->FParticle->createParticle(inf, PARTICLE_STONEAXE, COLLIDER_STONEAXE);

						timeShoot.start();
						status = PLAYER_SHOOT;
						previousStatus = PLAYER_IDLE;
					}
				}

				if (status == PLAYER_DOUBLEJUMP)
				{

					//SHOOT
					if (!timeShoot.isStarted() && App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && status != PLAYER_CROUCH && status != PLAYER_LOOKUP && status != PLAYER_SHOOT && status != PLAYER_SHOOTCROUCH && status != PLAYER_SHOOTLOOKUP)
					{
						infoParticle inf;

						inf.anim = this->stoneAxe;
						inf.text = this->graphicsStoneAxe;
						inf.position.x = this->position.x;
						inf.position.y = this->position.y;
						inf.speed.x = 2.0;
						inf.speed.y = 0.4;
						if (facingRight)
						{
							inf.direction = SHOOTRIGHT;
						}
						else
						{
							inf.direction = SHOOTLEFT;
						}

						App->FParticle->createParticle(inf, PARTICLE_STONEAXE, COLLIDER_STONEAXE);

						timeShoot.start();
						//status = PLAYER_SHOOT;
						//previousStatus = PLAYER_IDLE;
					}
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

					//SHOOT normal while jumping
					if (!timeShoot.isStarted() &&  App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && status != PLAYER_CROUCH && status != PLAYER_LOOKUP && status != PLAYER_SHOOT)
					{
						if (App->input->GetKey(SDL_SCANCODE_W))
						{
							infoParticle inf;

							inf.anim = this->stoneAxe;
							inf.text = this->graphicsStoneAxe;
							inf.position.x = this->position.x;
							inf.position.y = this->position.y;
							inf.speed.x = 0;
							inf.speed.y = 3.0;
							inf.direction = SHOOTUP;
							App->FParticle->createParticle(inf, PARTICLE_STONEAXE, COLLIDER_STONEAXE);
							timeShoot.start();
							//timeShootLookUp.start();
						}
						else
						{
							infoParticle inf;

							inf.anim = this->stoneAxe;
							inf.text = this->graphicsStoneAxe;
							inf.position.x = this->position.x;
							inf.position.y = this->position.y;
							inf.speed.x = 2.0;
							inf.speed.y = 0.4;
							if (facingRight)
							{
								inf.direction = SHOOTRIGHT;
							}
							else
							{
								inf.direction = SHOOTLEFT;
							}

							App->FParticle->createParticle(inf, PARTICLE_STONEAXE, COLLIDER_STONEAXE);

							timeShoot.start();
							//status = PLAYER_SHOOT;
							//previousStatus = PLAYER_JUMP;
						}
						
					}


				} //starting to fall
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

				if (status == PLAYER_FALLING /* || status == PLAYER_IDLE || status == PLAYER_SHOOT*/)
				{

					if (timeJump.getTicks() >= 670)
					{
						gravity = GRAVITY +0.5;
					}

					if (timeDoubleJump.getTicks() >= 800)
					{
						gravity = GRAVITY + 0.7;
					}

					if (!grounded){

						//SHOOT while falling
						if (!timeShoot.isStarted() &&  App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && status != PLAYER_CROUCH && status != PLAYER_LOOKUP && status != PLAYER_SHOOT)
						{
							infoParticle inf;

							inf.anim = this->stoneAxe;
							inf.text = this->graphicsStoneAxe;
							inf.position.x = this->position.x;
							inf.position.y = this->position.y;
							inf.speed.x = 2.0;
							inf.speed.y = 0.4;
							if (facingRight)
							{
								inf.direction = SHOOTRIGHT;
							}
							else
							{
								inf.direction = SHOOTLEFT;
							}
							App->FParticle->createParticle(inf, PARTICLE_STONEAXE, COLLIDER_STONEAXE);

							timeShoot.start();
							//status = PLAYER_SHOOT;
							//previousStatus = PLAYER_FALLING;
						}

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
				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && status != PLAYER_CROUCH && status != PLAYER_SHOOT && status != PLAYER_SHOOTCROUCH && status != PLAYER_SHOOTLOOKUP)
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
				if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && status != PLAYER_CROUCH && status != PLAYER_SHOOT && status != PLAYER_SHOOTCROUCH && status != PLAYER_SHOOTLOOKUP)
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

				if (status == PLAYER_CROUCH)
				{
					//SHOOT while falling
					if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN  && status != PLAYER_LOOKUP && status != PLAYER_SHOOT && status != PLAYER_SHOOTCROUCH)
					{

						infoParticle inf;

						inf.anim = this->stoneAxe;
						inf.text = this->graphicsStoneAxe;
						inf.position.x = this->position.x;
						inf.position.y = this->position.y;
						inf.speed.x = 2.0;
						inf.speed.y = 0.4;
						if (facingRight)
						{
							inf.direction = SHOOTRIGHT;
						}
						else
						{
							inf.direction = SHOOTLEFT;
						}
						App->FParticle->createParticle(inf, PARTICLE_STONEAXE, COLLIDER_STONEAXE);

						timeShootCrouch.start();
						status = PLAYER_SHOOTCROUCH;
						previousStatus = PLAYER_CROUCH;
					}
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
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT  && status != PLAYER_SHOOTLOOKUP)
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

			
				if (status == PLAYER_LOOKUP)
				{
					//SHOOT while falling
					if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN  && status != PLAYER_CROUCH && status != PLAYER_SHOOT && status != PLAYER_SHOOTLOOKUP)
					{
						infoParticle inf;

						inf.anim = this->stoneAxe;
						inf.text = this->graphicsStoneAxe;
						inf.position.x = this->position.x;
						inf.position.y = this->position.y;
						inf.speed.x = 0;
						inf.speed.y = 3.0;
						inf.direction = SHOOTUP;
						App->FParticle->createParticle(inf, PARTICLE_STONEAXE, COLLIDER_STONEAXE);

						timeShootLookUp.start();
						status = PLAYER_SHOOTLOOKUP;
						previousStatus = PLAYER_LOOKUP;
						shootLookUpF();
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
				if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN  && !jumping && status != PLAYER_CROUCH && status != PLAYER_SHOOTCROUCH && status != PLAYER_SHOOTLOOKUP)
				{
					status = PLAYER_JUMP;
					previousStatus = PLAYER_IDLE;
					jumpF();
				}

				

				if (status == PLAYER_SHOOT && timeShoot.isStarted() && timeShoot.getTicks() >= 300)
				{
					status = PLAYER_IDLE;
					previousStatus = PLAYER_SHOOT;
					shoot.Reset();
					timeShoot.stop();
				}

				if (status == PLAYER_JUMP || status == PLAYER_DOUBLEJUMP || status == PLAYER_FALLING && timeShoot.isStarted() && timeShoot.getTicks() >= 600)
				{		
					shoot.Reset();
					timeShoot.stop();
				}

				if (status == PLAYER_SHOOTCROUCH && timeShootCrouch.isStarted() && timeShootCrouch.getTicks() >= 300)
				{
					status = previousStatus;
					previousStatus = PLAYER_SHOOTCROUCH;
					shootCrouch.Reset();
					timeShootCrouch.stop();
				}
				
				//SHOOT LOOKUP
				if (status == PLAYER_SHOOTLOOKUP && timeShootLookUp.isStarted() && timeShootLookUp.getTicks() >= 300)
				{
					status = previousStatus;
					previousStatus = PLAYER_SHOOTLOOKUP;
					shootLookUp.Reset();
					timeShootLookUp.stop();
					endShootLookUpF();
				}

				if (grounded)
				{
					timeJump.stop();
					timeDoubleJump.stop();
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
			//LOG("IDLE");
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
			//LOG("FALLING");
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
			//LOG("WALKING");
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
			//LOG("CROUCH");
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
			//LOG("LOOKUP");
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
			//LOG("JUMP");
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
			//LOG("DOUBLEJUMP");
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
			//LOG("SHOOT");
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

		case PLAYER_SHOOTLOOKUP:
		{
			//LOG("SHOOTLOOKUP");
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(shootLookUp.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(shootLookUp.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
			}
		}

		break;

		case PLAYER_SHOOTCROUCH:
		{
			//LOG("SHOOTCROUCH");
			if (facingRight)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(shootCrouch.GetCurrentFrame()), SDL_FLIP_NONE, 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(shootCrouch.GetCurrentFrame()), SDL_FLIP_HORIZONTAL, 1.0f);
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



update_status Player::shootLookUpF()
{
	//position.y -= 9;
	//position.x -= 5;

	return UPDATE_CONTINUE;
}

update_status Player::endShootLookUpF()
{
	//position.y += 9;
	//position.x += 5;

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
		//LOG("ESTOY EN SUELO");
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

	case COLLIDER_MOVECAMERA:
	{
		
		App->renderer->camera.x -= 3;
		App->scene->moveUI();
	}

	break;

	case COLLIDER_STARTLEVEL:
	{
		position.x += speed.x;
	}

	break;

	default:

		break;
	}
}

void Player::OnCollisionEnter(Collider* c1, Collider* c2)
{
	switch (c2->type)
	{

	case COLLIDER_GROUND:
	{
		//LOG("ENTRO SUELO");
		
	}
	break;

	default:

		break;
	}

}

void Player::OnCollisionExit(Collider* c1, Collider* c2)
{
	switch (c2->type)
	{

	case COLLIDER_GROUND:
	{

		//LOG("SALGO SUELO");
	}
	break;

	default:

		break;
	}
}
