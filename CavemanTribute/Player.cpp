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

Player::Player(infoGameObject inf)
{
	//Initialization
	this->type = PLAYER;

	nLives = 2;

	bigShoot = false;
	longShoot = false;

	position = inf.position;
	
	speed.x = PLAYER_NORMAL_SPEED;
	speed.y = 0;

	status = PLAYER_IDLE_LEFT;
	previousStatus = PLAYER_IDLE_LEFT;

	running = false;

	//Animations

	//idle left
	idleLeft.frames.push_back({ 41, 13, 89, 117 });
	idleLeft.speed = 0.2f;

	//idle right
	idleRight.frames.push_back({ 608, 13, 89, 117 });
	idleRight.speed = 0.2f;

	//walking left
	walkingLeft.frames.push_back({ 183, 13, 66, 117 });
	walkingLeft.frames.push_back({ 332, 8, 75, 122 });
	walkingLeft.frames.push_back({ 479, 8, 66, 122 });
	walkingLeft.speed = 0.2f;

	//walking right

	walkingRight.frames.push_back({ 783, 13, 66, 117 });
	walkingRight.frames.push_back({ 918, 8, 89, 122 });
	walkingRight.frames.push_back({ 1070, 8, 75, 122 });
	walkingRight.speed = 0.2f;

	//running left
	runningLeft.frames.push_back({ 22, 450, 108, 121 });
	runningLeft.frames.push_back({ 179, 450, 94, 117 });
	runningLeft.frames.push_back({ 322, 450, 102, 117 });
	runningLeft.speed = 0.5f;

	//running right
	runningRight.frames.push_back({ 459, 450, 108, 121 });
	runningRight.frames.push_back({ 611, 450, 94, 117 });
	runningRight.frames.push_back({ 754, 450, 102, 117 });
	runningRight.speed = 0.5f;

	//jumping left
	jumpingLeft.frames.push_back({26, 147, 85, 131});
	jumpingLeft.frames.push_back({170, 156, 94,117});
	jumpingLeft.frames.push_back({326,151,84,99});
	jumpingLeft.frames.push_back({473,156,84,94});
	jumpingLeft.frames.push_back({615,156,84,117});
	jumpingLeft.frames.push_back({772,165,85,105});
	jumpingLeft.frames.push_back({915,165,98,99});
	jumpingLeft.speed = 0.2f;

	//jumping right
	jumpingRight.frames.push_back({37,294,84,131});
	jumpingRight.frames.push_back({180,303,93,117});
	jumpingRight.frames.push_back({326,298,85,99});
	jumpingRight.frames.push_back({473,303,85,93});
	jumpingRight.frames.push_back({625,303,84,117});
	jumpingRight.frames.push_back({763,312,85,103});
	jumpingRight.frames.push_back({901,312,98,99});
	jumpingRight.speed = 0.2f;

	//trapped
	trapped.frames.push_back({9,1038,75,103});
	trapped.frames.push_back({174,1029,94,84});
	trapped.frames.push_back({335,1052,100,80});
	trapped.speed = 0.2f;


	//shoting left
	shootingLeft.frames.push_back({ 32, 882, 85, 131 });
	shootingLeft.frames.push_back({ 147, 896, 121, 117 });
	shootingLeft.speed = 0.2f;

	//shoting right

	shootingRight.frames.push_back({ 621, 883, 85 ,128 });
	shootingRight.frames.push_back({ 763, 896,119, 117 });
	shootingRight.speed = 0.2f;

	//soft shoot left
	softShootLeft.frames.push_back({ 141, 9, 27, 43 });
	softShootLeft.frames.push_back({ 205, 9, 27, 43 });
	softShootLeft.speed = 0.2f;

	//soft shoot right
	softShootRight.frames.push_back({ 25, 9, 27, 43 });
	softShootRight.frames.push_back({ 89, 9, 27, 43 });
	softShootRight.speed = 0.2f;

	//hard shoot left
	hardShootLeft.frames.push_back({ 133, 61, 55, 63 });
	hardShootLeft.frames.push_back({ 196, 60, 55, 63 });
	hardShootLeft.speed = 0.2f;

	//hard shoot right
	hardShootRight.frames.push_back({ 5, 60, 55, 63 });
	hardShootRight.frames.push_back({ 69, 60, 55, 63 });
	hardShootRight.speed = 0.2f;

	//shoot explosion
	shootExplosion.frames.push_back({336,74,30,36});
	shootExplosion.frames.push_back({277,73,30,36});
	shootExplosion.frames.push_back({270,10,46,47});
	shootExplosion.frames.push_back({328,10,47,47});
	shootExplosion.loop = false;
	shootExplosion.speed = 0.2f;

	//snowAppear
	snowAppear.frames.push_back({32,123,99,83});
	snowAppear.frames.push_back({324,103,126,103});
	snowAppear.frames.push_back({610,75,164,131});
	snowAppear.frames.push_back({882,32,197,174});
	snowAppear.frames.push_back({1174,0,224,206});
	snowAppear.frames.push_back({1484,0,215,206});
	snowAppear.frames.push_back({1784,0,196,206});
	snowAppear.loop = false;
	snowAppear.speed = 0.2f;

	//flying
	flying.frames.push_back({27,1175,93,147});
	flying.frames.push_back({175,1176,93,140});
	flying.speed = 0.2f;

	//dying
	dying.frames.push_back({13,1324,127,144});
	dying.frames.push_back({156,1328,131,131});
	dying.frames.push_back({308,1361,122,112});
	dying.frames.push_back({450,1361,132,98});
	dying.frames.push_back({593,1361,140,70});
	dying.frames.push_back({739,1361,141,51});
	dying.frames.push_back({883,1361,146,28});
	dying.frames.push_back({900,900,10,10});
	dying.loop = false;
	dying.speed = 0.2f;

	

}

Player::~Player()
{

}

bool Player::Start()
{
	graphicsPlayer = App->Ftextures->Load("player.png");
	graphicsEffectsPlayer = App->Ftextures->Load("shoot.png");
	graphicsSnowEffectPlayer = App->Ftextures->Load("snowappear.png");

	shotFx = App->Faudio->LoadFx("shot.ogg");
	jumpFx = App->Faudio->LoadFx("jump.ogg");
	pickObjectFx = App->Faudio->LoadFx("pickobject.ogg");
	dieFx = App->Faudio->LoadFx("playerdie.ogg");

	return true;
}

update_status Player::PreUpdate()
{
	while (!App->scene->pause)
	{
		
		if (status == PLAYER_FLYING)//if it's not flying we add a falling force
		{
			position.y -= 2;
		}

		//flying
		if (timeAnimationFlying.isStarted() && timeAnimationFlying.getTicks() > PLAYER_FLYING_TIME)
		{
			timeAnimationFlying.stop();
			status = PLAYER_IDLE_LEFT;
			
		}

		//reborn
		if (timeAnimationDyingButStillLives.isStarted() && timeAnimationDyingButStillLives.getTicks() > 3000)
		{
			timeAnimationDyingButStillLives.stop();
			timeAnimationReborn.start();

			status = PLAYER_REBORN;

			if (App->scene->nLevel == 1)
			{
				position.x = SCREEN_WIDTH / 2;
				position.y = 235;
			}
			else if (App->scene->nLevel == 2)
			{
				position.x = SCREEN_WIDTH / 2;
				position.y = -90;
			}

			timeAnimationDyingButStillLives.stop();
			dying.Reset();
			running = false;
			bigShoot = false;

		}

		if (timeAnimationReborn.isStarted() && timeAnimationReborn.getTicks() > 2000)
		{
			godMode = false;
			status = PLAYER_IDLE_LEFT;
			previousStatus = PLAYER_IDLE_LEFT;
			timeAnimationReborn.stop();
			snowAppear.Reset();
		}



		//dying
		if (godMode == false)
		{
			if (timeAnimationDying.isStarted() && timeAnimationDying.getTicks() > 500)
			{
				dead = true;
				colliderBody->to_delete = true;
				colliderFoot->to_delete = true;
			}
		}

		//Main state machine loop
		if (status != PLAYER_DYING && status != PLAYER_TRAPPED && status != PLAYER_FLYING)
		{

			//god mode
			if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
				godMode = !godMode;

			//speed mode
			if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
				running = !running;

			//big shoot mode
			if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)
				bigShoot = !bigShoot;

			//big shoot mode
			if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
				longShoot = !longShoot;


			if (running)
			{
				speed.x = PLAYER_HIGH_SPEED;
			}
			else
			{
				speed.x = PLAYER_NORMAL_SPEED;
			}

			if (status != PLAYER_FLYING)
			{

				position.y += 2;

			}


			//shooting time anim
			if (timeShooting.isStarted() && timeShooting.getTicks() > 80)
			{
				timeShooting.stop();
				status = previousStatus;

				if (status == PLAYER_JUMPING_LEFT)
				{
					previousStatus = PLAYER_SHOOTING_LEFT;
					status = PLAYER_IDLE_LEFT;
				}

				if (status == PLAYER_JUMPING_RIGHT)
				{
					previousStatus = PLAYER_SHOOTING_RIGHT;
					status = PLAYER_IDLE_RIGHT;
				}

				return UPDATE_CONTINUE;
			}

			//shooting right
			if (App->input->GetKey(SDL_SCANCODE_P) == KEY_UP)
			{
				if (status == PLAYER_IDLE_RIGHT || status == PLAYER_WALKING_RIGHT || status == PLAYER_JUMPING_RIGHT)
				{

					App->Faudio->PlayFx(shotFx);

					infoParticle inf;
					if (bigShoot)
					{
						inf.anim = this->hardShootRight;

					}
					else
					{
						inf.anim = this->softShootRight;
					}
					inf.explo = this->shootExplosion;
					inf.text = this->graphicsEffectsPlayer;
					inf.position.x = this->position.x;
					inf.position.y = this->position.y;
					
					if (longShoot == false)
					{
						inf.speed.x = 5.0;
					}
					else
					{
						inf.speed.x = 7.0;
					}
					

					if (bigShoot)
					{
						App->FParticle->createParticle(inf, PARTICLE_HARDSHOT, COLLIDER_PLAYER_HARD_SHOT);
					}
					else
					{
						App->FParticle->createParticle(inf, PARTICLE_SOFTSHOT, COLLIDER_PLAYER_SOFT_SHOT);
					}

					previousStatus = status;
					status = PLAYER_SHOOTING_RIGHT;
					timeShooting.start();

				}

				//shooting left
				if (this->status == PLAYER_IDLE_LEFT || this->status == PLAYER_WALKING_LEFT || status == PLAYER_JUMPING_LEFT)
				{
					App->Faudio->PlayFx(shotFx);

					infoParticle inf;
					if (bigShoot)
					{
						inf.anim = this->hardShootLeft;
					}
					else
					{
						inf.anim = this->softShootLeft;
					}
					inf.explo = this->shootExplosion;
					inf.text = this->graphicsEffectsPlayer;
					inf.position.x = this->position.x;
					inf.position.y = this->position.y;
					
					if (longShoot == false)
					{
						inf.speed.x = -5.0;
					}
					else
					{
						inf.speed.x = -7.0;
					}


					if (bigShoot)
					{
						App->FParticle->createParticle(inf, PARTICLE_HARDSHOT, COLLIDER_PLAYER_HARD_SHOT);
					}
					else
					{
						App->FParticle->createParticle(inf, PARTICLE_SOFTSHOT, COLLIDER_PLAYER_SOFT_SHOT);
					}

					previousStatus = status;
					status = PLAYER_SHOOTING_LEFT;
					timeShooting.start();
				}
			}


			//walking right
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				if (status != PLAYER_JUMPING_RIGHT  && timeAnimationJump.getTicks() <= PLAYER_JUMP_TIME)
				{
					if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
					{
						if (!timeAnimationJump.isStarted())
						{
							App->Faudio->PlayFx(jumpFx);

							position.y -= PLAYER_COLLIDER_BODY_HEIGHT + 12;
							status = PLAYER_JUMPING_RIGHT;

							this->timeAnimationJump.start();
							return UPDATE_CONTINUE;

						}
					}
					else
					{	//player is shooting while walking right
						if (status != PLAYER_SHOOTING_RIGHT)
						{
							this->status = PLAYER_WALKING_RIGHT;
							this->previousStatus = PLAYER_IDLE_RIGHT;
						}
					}


				}

				/*the player jumps and shot at a very close time, so we have to control it in order to prevent that the previous status will be shooting
				if it's happens, when the character ends the jump, it will continue doind the shooting animation
				this code prevents it*/
				if (this->timeAnimationJump.getTicks() >= PLAYER_JUMP_TIME)
				{
					timeAnimationJump.stop();


					if (previousStatus == PLAYER_SHOOTING_RIGHT)
					{
						status = PLAYER_IDLE_RIGHT;
					}
					else
					{
						status = previousStatus;
					}


				}

				previousStatus = PLAYER_IDLE_RIGHT;

				position.x += speed.x;


				return UPDATE_CONTINUE;
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && previousStatus == PLAYER_IDLE_RIGHT && status != PLAYER_JUMPING_RIGHT && status != PLAYER_SHOOTING_RIGHT)
			{

				this->status = PLAYER_IDLE_RIGHT;
				this->previousStatus = PLAYER_WALKING_RIGHT;


				return UPDATE_CONTINUE;

			}



			//walking left
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{

				if (status != PLAYER_JUMPING_LEFT && timeAnimationJump.getTicks() <= PLAYER_JUMP_TIME)
				{
					//player jumps while going left
					if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
					{
						if (!timeAnimationJump.isStarted())
						{
							App->Faudio->PlayFx(jumpFx);

							position.y -= PLAYER_COLLIDER_BODY_HEIGHT + 12;
							status = PLAYER_JUMPING_LEFT;

							this->timeAnimationJump.start();
							return UPDATE_CONTINUE;
						}
					}
					else
					{
						//player is shooting while going left
						if (status != PLAYER_SHOOTING_LEFT)
						{
							this->status = PLAYER_WALKING_LEFT;
							this->previousStatus = PLAYER_IDLE_LEFT;
						}

					}
				}

				/*the player jumps and shot at a very close time, so we have to control it in order to prevent that the previous status will be shooting
				if it's happens, when the character ends the jump, it will continue doind the shooting animation
				this code prevents it*/
				if (this->timeAnimationJump.getTicks() >= PLAYER_JUMP_TIME)
				{
					timeAnimationJump.stop();
					if (previousStatus == PLAYER_SHOOTING_LEFT)
					{
						status = PLAYER_IDLE_LEFT;
					}
					else
					{
						status = previousStatus;
					}

				}


				previousStatus = PLAYER_IDLE_LEFT;

				position.x -= speed.x;



				return UPDATE_CONTINUE;
			}

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && previousStatus == PLAYER_IDLE_LEFT  && status != PLAYER_JUMPING_LEFT && status != PLAYER_SHOOTING_LEFT && status != PLAYER_IDLE_LEFT)
			{

				this->status = PLAYER_IDLE_LEFT;
				this->previousStatus = PLAYER_WALKING_LEFT;

				return UPDATE_CONTINUE;

			}

			//jumping
			if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN && status != PLAYER_JUMPING_LEFT && status != PLAYER_JUMPING_RIGHT && this->timeAnimationJump.getTicks() < PLAYER_JUMP_TIME)
			{
				if (!timeAnimationJump.isStarted())
				{
					App->Faudio->PlayFx(jumpFx);
					position.y -= PLAYER_COLLIDER_BODY_HEIGHT + 12;

					previousStatus = status;
					this->timeAnimationJump.start();

					if (status == PLAYER_IDLE_LEFT)
					{
						status = PLAYER_JUMPING_LEFT;
					}

					if (status == PLAYER_IDLE_RIGHT)
					{
						status = PLAYER_JUMPING_RIGHT;
					}


				}

				return UPDATE_CONTINUE;

			}

			//jump
			if (this->timeAnimationJump.getTicks() >= PLAYER_JUMP_TIME)
			{
				timeAnimationJump.stop();
				if (previousStatus == PLAYER_SHOOTING_LEFT)
				{
					status = PLAYER_IDLE_LEFT;
				}
				else if (previousStatus == PLAYER_SHOOTING_RIGHT)
				{
					status = PLAYER_IDLE_RIGHT;
				}
				else
				{
					status = previousStatus;
				}


				return UPDATE_CONTINUE;
			}

		}

		

		return UPDATE_CONTINUE;
	}



	return UPDATE_CONTINUE;

}

update_status Player::Update()
{
	
		colliderBody->SetPos(position.x, position.y);
		colliderFoot->SetPos(position.x, (position.y + PLAYER_COLLIDER_BODY_HEIGHT));

		switch (status)
		{
		case PLAYER_IDLE_RIGHT:
		{
			if (running)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(runningRight.GetCurrentFrame()), 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(idleRight.GetCurrentFrame()), 1.0f);
			}
		}

		break;
		case PLAYER_IDLE_LEFT:
		{
			if (running)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(runningLeft.GetCurrentFrame()), 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(idleLeft.GetCurrentFrame()), 1.0f);
			}
		}

		break;
		case PLAYER_WALKING_LEFT:
		{
			if (running)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(runningLeft.GetCurrentFrame()), 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(walkingLeft.GetCurrentFrame()), 1.0f);
			}
		}
		break;
		case PLAYER_WALKING_RIGHT:
		{
			if (running)
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(runningRight.GetCurrentFrame()), 1.0f);
			}
			else
			{
				App->renderer->Blit(graphicsPlayer, position.x, position.y, &(walkingRight.GetCurrentFrame()), 1.0f);
			}
		}
		break;

		case PLAYER_JUMPING_LEFT:
			App->renderer->Blit(graphicsPlayer, position.x, position.y, &(jumpingLeft.GetCurrentFrame()), 1.0f);
			break;
		case PLAYER_JUMPING_RIGHT:
			App->renderer->Blit(graphicsPlayer, position.x, position.y, &(jumpingRight.GetCurrentFrame()), 1.0f);
			break;
		case PLAYER_SHOOTING_LEFT:
			App->renderer->Blit(graphicsPlayer, position.x, position.y, &(shootingLeft.GetCurrentFrame()), 1.0f);
			break;
		case PLAYER_SHOOTING_RIGHT:
			App->renderer->Blit(graphicsPlayer, position.x, position.y, &(shootingRight.GetCurrentFrame()), 1.0f);
			break;
		case PLAYER_DYING:
			App->renderer->Blit(graphicsPlayer, position.x, position.y, &(dying.GetCurrentFrame()), 1.0f);
			break;
		case PLAYER_TRAPPED:
			App->renderer->Blit(graphicsPlayer, position.x + 5, position.y - 20, &(trapped.GetCurrentFrame()), 1.0f);
			break;
		case PLAYER_FLYING:
			App->renderer->Blit(graphicsPlayer, position.x + 5, position.y - 20, &(flying.GetCurrentFrame()), 1.0f);
			break;
		case PLAYER_FALLING_LEFT:
			App->renderer->Blit(graphicsPlayer, position.x + 5, position.y - 20, &(fallingLeft.GetCurrentFrame()), 1.0f);
			break;
		case PLAYER_REBORN:
			App->renderer->Blit(graphicsPlayer, position.x, position.y, &(idleLeft.GetCurrentFrame()), 1.0f);
			break;

		default:
			break;
		}

		return UPDATE_CONTINUE;

}


void Player::OnCollision(Collider* c1, Collider* c2)
{
	
	switch (c2->type)
	{

	case COLLIDER_PLATFORM:
	{
			
			if (c1->rect.y <= c2->rect.y)
			{
				position.y -= 2;
			}	
	}
		break;

	case COLLIDER_WALL:
	{
		if (status == PLAYER_WALKING_LEFT || status == PLAYER_JUMPING_LEFT)
		{
			if (!running)
			{
				position.x += PLAYER_NORMAL_SPEED;
			}
			else
			{
				position.x += PLAYER_HIGH_SPEED;
			}
		}

		if (status == PLAYER_WALKING_RIGHT ||status == PLAYER_JUMPING_RIGHT)
		{
			if (!running)
			{
				position.x -= PLAYER_NORMAL_SPEED;
			}
			else
			{
				position.x -= PLAYER_HIGH_SPEED;
			}
		}
	}
		break;

	case COLLIDER_PLATFORM_BORDER_LEFT_SPEC:
	{
		if (status == PLAYER_WALKING_LEFT || status == PLAYER_JUMPING_LEFT)
		{
			if (!running)
			{
				position.x += PLAYER_NORMAL_SPEED;
			}
			else
			{
				position.x += PLAYER_HIGH_SPEED;
			}
		}
	}
	break;

	case COLLIDER_PLATFORM_BORDER_RIGHT_SPEC:
	{
		if (status == PLAYER_WALKING_RIGHT || status == PLAYER_JUMPING_RIGHT)
		{
			if (!running)
			{
				position.x -= PLAYER_NORMAL_SPEED;
			}
			else
			{
				position.x -= PLAYER_HIGH_SPEED;
			}
		}
	}
	break;



	case COLLIDER_ENEMY:
	{
		if (godMode == false)
		{
			if (c2->active == true)
			{
				if (nLives > 0)
				{
					App->Faudio->PlayFx(dieFx);
					nLives--;
					App->scene->nPlayerLives--;
					timeAnimationDyingButStillLives.stop();
					timeAnimationDyingButStillLives.start();
					godMode = true;
					status = PLAYER_DYING;
				}
				else if (nLives == 0)
				{
					App->Faudio->PlayFx(dieFx);
					App->scene->nPlayerLives--;
					timeAnimationDying.start();
					status = PLAYER_DYING;
				}
			}
			
		}

		if (c2->rolling == true)
		{
			status = PLAYER_TRAPPED;
			this->position.x = c2->rect.x;
			this->position.y = c2->rect.y;
		}

		if (c2->launchable == true)
		{
			GameObject *aux = App->FGameObject->Owner(c2);

			if (status == PLAYER_SHOOTING_RIGHT || status == PLAYER_IDLE_RIGHT ||  status == PLAYER_WALKING_RIGHT)
			{
				if (App->input->GetKey(SDL_SCANCODE_P) == KEY_UP)
				{
				aux->roll(RIGHT);
				break;
				}

				if (status == PLAYER_WALKING_RIGHT && status != PLAYER_JUMPING_LEFT && status != PLAYER_JUMPING_RIGHT)
				{
					if (this->position.x + this->colliderBody->rect.w + aux->colliderBody->rect.w <= SCREEN_WIDTH)
					{
						aux->position.x = this->position.x + c1->rect.w;
					}
					
				}
			}

			if (status == PLAYER_SHOOTING_LEFT || status == PLAYER_IDLE_LEFT || status == PLAYER_WALKING_LEFT)
			{
				if (App->input->GetKey(SDL_SCANCODE_P) == KEY_UP)
				{
					aux->roll(LEFT);
					break;
				}

				if (status == PLAYER_WALKING_LEFT && status != PLAYER_JUMPING_LEFT && status != PLAYER_JUMPING_RIGHT)
				{
					if (this->position.x - aux->colliderBody->rect.w >= 0)
					{
						aux->position.x = this->position.x - c2->rect.w;
					}
				}

			}
		}		
		
	}
	break;

	case COLLIDER_POTION_RED:
	{
		if (running == false)
		{
			running = true;
		}

		App->Faudio->PlayFx(pickObjectFx);

		GameObject *potion = App->FGameObject->Owner(c2);

		if (potion != nullptr)
		{
			if (potion->colliderBody->to_delete != true)
			{
				potion->dead = true;
				potion->colliderBody->to_delete = true;
			}
		}
		
	}
	break;

	case COLLIDER_POTION_BLUE:
	{
		if (bigShoot == false)
		{
			bigShoot = true;
		}

		App->Faudio->PlayFx(pickObjectFx);

		GameObject *potion = App->FGameObject->Owner(c2);

		if (potion != nullptr)
		{
			if (potion->colliderBody->to_delete != true)
			{
				potion->dead = true;
				potion->colliderBody->to_delete = true;
			}
		}

	}
	break;

	case COLLIDER_POTION_YELLOW:
	{
		if (longShoot == false)
		{
			longShoot = true;
		}

		App->Faudio->PlayFx(pickObjectFx);

		GameObject *potion = App->FGameObject->Owner(c2);

		if (potion != nullptr)
		{
			if (potion->colliderBody->to_delete != true)
			{
				potion->dead = true;
				potion->colliderBody->to_delete = true;
			}
		}
	}
	break;

	default:
		break;
	}
}

void Player::stopRolling()
{
	if (status == PLAYER_TRAPPED)
	{
		status = PLAYER_IDLE_LEFT;
	}
}

void Player::fly()
{

		status = PLAYER_FLYING;
	timeAnimationFlying.start();


}


bool Player::CleanUp()
{
	App->Ftextures->Unload(graphicsPlayer);
	App->Ftextures->Unload(graphicsEffectsPlayer);
	App->Ftextures->Unload(graphicsSnowEffectPlayer);

	return true;
}
