#include "Globals.h"
#include "Application.h"
#include "MCollision.h"

#include "MRender.h"
#include "MTextures.h"
#include "MScene.h"
#include "MGameObject.h"
#include "Player.h"
#include "MIntro.h"
#include "MGameOver.h"
#include "MAudio.h"
#include "MInput.h"

MScene::MScene(bool start_enabled) : Module(start_enabled)
{
	background = NULL;
	nPlayerLives = 2;
	nEnemiesLeft = 4;

	//head icon
	headIcon.x = 1403;
	headIcon.y = 8;
	headIcon.w = 61;
	headIcon.h = 76;

	//number zero
	numberZero.x = 1390;
	numberZero.y = 105;
	numberZero.w = 31;
	numberZero.h = 31;

	//number one
	numberOne.x = 1458;
	numberOne.y = 105;
	numberOne.w = 23;
	numberOne.h = 31;
	
	//number two
	numberTwo.x = 1390;
	numberTwo.y = 169;
	numberTwo.w = 32;
	numberTwo.h = 31;


}

MScene::~MScene()
{

}


bool MScene::Start()
{
	nPlayerLives = 2;
	nEnemiesLeft = 5;
	nLevel = 1;
	levelOneDone = false;
	levelTwoDone = false;
	pause = false;

	background = App->Ftextures->Load("niveles.png");
	
	top = App->Ftextures->Load("top.png");
	graphicsPlayer = App->Ftextures->Load("player.png");

	createLevel();
	createPlayerAndEnemies(1);

	App->Faudio->PlayMusic("backgroundmusic.ogg", 1.0f);
	
	return true;
}

void MScene::createPlayerAndEnemies(int level)
{

	infoGameObject inf;
	GameObject* player = App->FGameObject->returnPlayer();

	switch (level)
	{
	case 1:

		

		inf.position = { SCREEN_WIDTH / 2, 235 };

		App->FGameObject->createGameObject(inf, PLAYER, COLLIDER_PLAYER);

		inf.position = { 110, 150 };
	
		inf.position = { 110, 40 };
		App->FGameObject->createGameObject(inf, ENEMY_ROSEGOBLIN, COLLIDER_ENEMY);

		inf.position = { 200, 40 };

		App->FGameObject->createGameObject(inf, ENEMY_ROSEGOBLIN, COLLIDER_ENEMY);

		inf.position = { 60, 110 };

		App->FGameObject->createGameObject(inf, ENEMY_ROSEGOBLIN, COLLIDER_ENEMY);

		inf.position = { 250, 110 };

		App->FGameObject->createGameObject(inf, ENEMY_ROSEGOBLIN, COLLIDER_ENEMY);

		inf.position = { SCREEN_WIDTH / 2, 150 };

		App->FGameObject->createGameObject(inf, ENEMY_ROSEGOBLIN, COLLIDER_ENEMY);

		break;

	case 2:

		player->position.x = SCREEN_WIDTH / 2;
		player->position.y = -90;

		inf.position = { 80, -280 };

		App->FGameObject->createGameObject(inf, ENEMY_YELLOWMONKEY, COLLIDER_ENEMY);

		inf.position = { 160, -280 };

		App->FGameObject->createGameObject(inf, ENEMY_YELLOWMONKEY, COLLIDER_ENEMY);

		inf.position = { 150, -195 };

		App->FGameObject->createGameObject(inf, ENEMY_YELLOWMONKEY, COLLIDER_ENEMY);

		inf.position = { 200, -150 };

		App->FGameObject->createGameObject(inf, ENEMY_YELLOWMONKEY, COLLIDER_ENEMY);

		inf.position = { 150, -150 };

		App->FGameObject->createGameObject(inf, ENEMY_YELLOWMONKEY, COLLIDER_ENEMY);

		break;
	default:
		break;
	}
}

void MScene::createLevel()
{
	//level 1

	
	//SIDE WALLL
	App->FCollision->AddCollider({ -20, 0, 20, SCREEN_HEIGHT }, COLLIDER_WALL, this);
	App->FCollision->AddCollider({ SCREEN_WIDTH, 0, 20, SCREEN_HEIGHT }, COLLIDER_WALL, this);

	//TOP WALL
	App->FCollision->AddCollider({ (TILE_WIDTH * 0), (TILE_WIDTH * 0), SCREEN_WIDTH, 20 }, COLLIDER_WALL, this);

	//GROUND WALL
	App->FCollision->AddCollider({ 0, SCREEN_HEIGHT - 15, SCREEN_WIDTH, 20 }, COLLIDER_WALL, this);

	//GROUND
	App->FCollision->AddCollider({ (TILE_WIDTH * 0), (SCREEN_HEIGHT - TILE_HEIGHT), SCREEN_WIDTH, 3 }, COLLIDER_PLATFORM, this);

	//PLATFORMS 1st level (from botton to top and left to right)

	//3 first

	//platform1
	App->FCollision->AddCollider({ (TILE_WIDTH * 0), SCREEN_HEIGHT - (TILE_HEIGHT * 3) - 6, (TILE_WIDTH * 4), 2 }, COLLIDER_PLATFORM, this);

	//border
	App->FCollision->AddCollider({ (TILE_WIDTH * 4), SCREEN_HEIGHT - (TILE_HEIGHT * 3) - 6, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_LEFT, this);

	//platform2
	App->FCollision->AddCollider({ (TILE_WIDTH * 6) + TILE_WIDTH / 2, SCREEN_HEIGHT - (TILE_HEIGHT * 3) - 6, (TILE_WIDTH * 4), 2 }, COLLIDER_PLATFORM, this);

	//borders
	App->FCollision->AddCollider({ (TILE_WIDTH * 6) + TILE_WIDTH / 2, SCREEN_HEIGHT - (TILE_HEIGHT * 3) - 6, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_RIGHT, this);
	App->FCollision->AddCollider({ (TILE_WIDTH * 6) + TILE_WIDTH / 2 + (TILE_WIDTH * 4), SCREEN_HEIGHT - (TILE_HEIGHT * 3) - 6, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_LEFT, this);

	//platform3
	App->FCollision->AddCollider({ (TILE_WIDTH * 13), SCREEN_HEIGHT - (TILE_HEIGHT * 3) - 6, (TILE_WIDTH * 4), 2 }, COLLIDER_PLATFORM, this);

	//border
	App->FCollision->AddCollider({ (TILE_WIDTH * 13), SCREEN_HEIGHT - (TILE_HEIGHT * 3) - 6, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_RIGHT, this);

	//platform4
	App->FCollision->AddCollider({ (TILE_WIDTH * 3) + 5, SCREEN_HEIGHT - (TILE_HEIGHT * 5) - 10, (TILE_WIDTH * 10) + TILE_WIDTH / 2, 2 }, COLLIDER_PLATFORM, this);

	//borders
	App->FCollision->AddCollider({ (TILE_WIDTH * 3) + 5, SCREEN_HEIGHT - (TILE_HEIGHT * 5) - 10, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_RIGHT, this);
	App->FCollision->AddCollider({ (TILE_WIDTH * 3) + 5 + (TILE_WIDTH * 10) + TILE_WIDTH / 2, SCREEN_HEIGHT - (TILE_HEIGHT * 5) - 10, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_LEFT, this);

	//platform5
	App->FCollision->AddCollider({ (TILE_WIDTH * 0), SCREEN_HEIGHT - (TILE_HEIGHT * 7) - TILE_HEIGHT / 2, (TILE_WIDTH * 7) + 7, 2 }, COLLIDER_PLATFORM, this);

	//border
	App->FCollision->AddCollider({ (TILE_WIDTH * 0) + (TILE_WIDTH * 7) + 7, SCREEN_HEIGHT - (TILE_HEIGHT * 7) - TILE_HEIGHT / 2, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_LEFT, this);

	//platform6
	App->FCollision->AddCollider({ (TILE_WIDTH * 9) + TILE_WIDTH / 2 + 2, SCREEN_HEIGHT - (TILE_HEIGHT * 7) - TILE_HEIGHT / 2, (TILE_WIDTH * 7) + TILE_WIDTH / 2, 2 }, COLLIDER_PLATFORM, this);

	//border
	App->FCollision->AddCollider({ (TILE_WIDTH * 9) + TILE_WIDTH / 2 + 2, SCREEN_HEIGHT - (TILE_HEIGHT * 7) - TILE_HEIGHT / 2, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_RIGHT, this);

	//platform7
	App->FCollision->AddCollider({ (TILE_WIDTH * 2) + 5, SCREEN_HEIGHT - (TILE_HEIGHT * 10) + 6, (TILE_WIDTH * 2), 2 }, COLLIDER_PLATFORM, this);
	App->FCollision->AddCollider({ (TILE_WIDTH * 8) + TILE_WIDTH / 2 + (TILE_WIDTH * 4) + 5, SCREEN_HEIGHT - (TILE_HEIGHT * 10) + 6, (TILE_WIDTH * 2), 2 }, COLLIDER_PLATFORM, this);

	//borders
	App->FCollision->AddCollider({ (TILE_WIDTH * 2) + 5, SCREEN_HEIGHT - (TILE_HEIGHT * 10) + 6, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_RIGHT, this);
	App->FCollision->AddCollider({ (TILE_WIDTH * 2) + 5 + (TILE_WIDTH * 12) + TILE_WIDTH / 2, SCREEN_HEIGHT - (TILE_HEIGHT * 10) + 6, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_RIGHT, this);

	//platform8
	App->FCollision->AddCollider({ (TILE_WIDTH * 4) + 5, SCREEN_HEIGHT - (TILE_HEIGHT * 11) + 6, (TILE_WIDTH * 8) + TILE_WIDTH / 2, 2 }, COLLIDER_PLATFORM, this);

	//borders
	App->FCollision->AddCollider({ (TILE_WIDTH * 4) + 3, SCREEN_HEIGHT - (TILE_HEIGHT * 11) + 6, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_RIGHT_SPEC, this);
	App->FCollision->AddCollider({ (TILE_WIDTH * 4) + 5 + (TILE_WIDTH * 8) + TILE_WIDTH / 2, SCREEN_HEIGHT - (TILE_HEIGHT * 11) + 6, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_LEFT_SPEC, this);

	//player and enemies

	

	
	//level 2


	//SIDE WALLL
	App->FCollision->AddCollider({ -20, -SCREEN_HEIGHT, 20, SCREEN_HEIGHT }, COLLIDER_WALL, this);
	App->FCollision->AddCollider({ SCREEN_WIDTH, -SCREEN_HEIGHT, 20, SCREEN_HEIGHT }, COLLIDER_WALL, this);

	//TOP WALL
	App->FCollision->AddCollider({ (TILE_WIDTH * 0), -SCREEN_HEIGHT - 20, SCREEN_WIDTH, 20 }, COLLIDER_WALL, this);

	//GROUND WALL
	App->FCollision->AddCollider({ 0, -20, SCREEN_WIDTH, 20 }, COLLIDER_WALL, this);

	//GROUND
	App->FCollision->AddCollider({ (TILE_WIDTH * 0), -(TILE_HEIGHT+3), SCREEN_WIDTH, 3 }, COLLIDER_PLATFORM, this);

	//platform1
	App->FCollision->AddCollider({ (TILE_WIDTH * 4) +3, -(TILE_HEIGHT *4) +8 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 9) + TILE_WIDTH / 2, 2 }, COLLIDER_PLATFORM, this);

	//border
	App->FCollision->AddCollider({ (TILE_WIDTH * 13) + TILE_WIDTH / 2 +3, -(TILE_HEIGHT * 4) + 8 + TILE_HEIGHT / 2 - 3, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_LEFT, this);

	//platform2
	App->FCollision->AddCollider({ (TILE_WIDTH * 6) + 7	, -(TILE_HEIGHT * 6) + 6 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 7), 2 }, COLLIDER_PLATFORM, this);

	App->FCollision->AddCollider({ (TILE_WIDTH * 2) + 5, -(TILE_HEIGHT * 6) + 6 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 2), 2 }, COLLIDER_PLATFORM, this);

	//border
	App->FCollision->AddCollider({ (TILE_WIDTH * 6) + 7 , -(TILE_HEIGHT * 6) + 7 + TILE_HEIGHT / 2 - 3, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_RIGHT, this);

	//block1
	App->FCollision->AddCollider({ (TILE_WIDTH * 2) , -(TILE_HEIGHT * 6) + 8 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 2), TILE_HEIGHT * 1 }, COLLIDER_WALL, this);

	//platform3
	App->FCollision->AddCollider({ (TILE_WIDTH * 4) + 3, -(TILE_HEIGHT * 8) + 3 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 6) + TILE_WIDTH / 2, 2 }, COLLIDER_PLATFORM, this);

	App->FCollision->AddCollider({ (TILE_WIDTH * 13) -1, -(TILE_HEIGHT * 8) + 3 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 2), 2 }, COLLIDER_PLATFORM, this);

	//border
	App->FCollision->AddCollider({ (TILE_WIDTH * 10) + 8, -(TILE_HEIGHT * 8) + 4 + TILE_HEIGHT / 2 - 3, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_LEFT, this);

	//block2
	App->FCollision->AddCollider({ (TILE_WIDTH * 13), -(TILE_HEIGHT * 8) + 6 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 2), TILE_HEIGHT * 1 }, COLLIDER_WALL, this);

	//platform4
	App->FCollision->AddCollider({ (TILE_WIDTH * 6) + 7, -(TILE_HEIGHT * 10) + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 7), 2 }, COLLIDER_PLATFORM, this);

	App->FCollision->AddCollider({ (TILE_WIDTH * 2) + 5, -(TILE_HEIGHT * 10) + 10 - TILE_HEIGHT /2 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 2), 2 }, COLLIDER_PLATFORM, this);

	//border
	App->FCollision->AddCollider({ (TILE_WIDTH * 6) + 7, -(TILE_HEIGHT * 10) + TILE_HEIGHT / 2 - 3, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_RIGHT, this);

	//block3
	App->FCollision->AddCollider({ (TILE_WIDTH * 2) , -(TILE_HEIGHT * 10) + 13 - TILE_HEIGHT / 2 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 2), TILE_HEIGHT * 1 }, COLLIDER_WALL, this);

	//platform5
	App->FCollision->AddCollider({ (TILE_WIDTH * 3) + 3, -(TILE_HEIGHT *12) -3 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 7) + TILE_WIDTH / 2, 2 }, COLLIDER_PLATFORM, this);

	App->FCollision->AddCollider({ (TILE_WIDTH * 13), -(TILE_HEIGHT * 12) - 3 + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 2), 2 }, COLLIDER_PLATFORM, this);

	//border
	App->FCollision->AddCollider({ (TILE_WIDTH * 10) + 10, -(TILE_HEIGHT * 12) - 3 + TILE_HEIGHT / 2 - 3, 2, TILE_HEIGHT }, COLLIDER_PLATFORM_BORDER_LEFT, this);

	//block4
	App->FCollision->AddCollider({ (TILE_WIDTH * 13) , -(TILE_HEIGHT * 12) + TILE_HEIGHT / 2 - 3, (TILE_WIDTH * 2), TILE_HEIGHT * 1 }, COLLIDER_WALL, this);




	
}


bool MScene::CleanUp()
{

	App->Ftextures->Unload(background);
	App->Ftextures->Unload(top);
	App->Ftextures->Unload(graphicsPlayer);

	return true;
}


update_status MScene::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		pause = !pause;
	}

	
		App->renderer->Blit(background, 0, -280, NULL);

		if (nLevel == 1)
		{
			App->renderer->Blit(graphicsPlayer, 5, 20, &headIcon);
			App->renderer->Blit(top, 0, 0, NULL);
		}
		else if (nLevel == 2)
		{
			App->renderer->Blit(graphicsPlayer, 5, -280, &headIcon);
			App->renderer->Blit(top, 0, -300, NULL);
		}


		switch (nPlayerLives)
		{
		case 0:
		{
			if (nLevel == 1)
			{
				App->renderer->Blit(graphicsPlayer, 30, 30, &numberZero);
			}
			else if (nLevel == 2)
			{
				App->renderer->Blit(graphicsPlayer, 30, -270, &numberZero);
			}
		}
		break;

		case 1:
		{
			if (nLevel == 1)
			{
				App->renderer->Blit(graphicsPlayer, 30, 30, &numberOne);
			}
			else if (nLevel == 2)
			{
				App->renderer->Blit(graphicsPlayer, 30, -270, &numberOne);
			}

		}

		break;

		case 2:
		{
			if (nLevel == 1)
			{
				App->renderer->Blit(graphicsPlayer, 30, 30, &numberTwo);
			}
			else if (nLevel == 2)
			{
				App->renderer->Blit(graphicsPlayer, 30, -270, &numberTwo);

			}

		}

		break;
		default:
			break;
		}

		//player die 
		if (nPlayerLives < 0 && !timeGameOver.isStarted())
		{
			timeGameOver.start();

		}

		//game over
		if (timeGameOver.isStarted() && timeGameOver.getTicks() > 2000)
		{
			App->Faudio->PlayMusic("", 1.0f);
			App->FGameObject->Disable();
			App->FCollision->Disable();
			App->renderer->camera.y = 0;
			timeGameOver.stop();
			this->Disable();
			App->gameover->Enable();
			return UPDATE_CONTINUE;

		}

		//first level done 
		if (nLevel == 1 && nEnemiesLeft == 0)
		{
			nLevel = 2;
			levelOneDone = true;
		}


		// intro second level
		if (nLevel == 2 && !timeChangeLevel.isStarted() && nEnemiesLeft == 0 && levelOneDone == true)
		{
			GameObject* player = App->FGameObject->returnPlayer();
			player->fly();
			timeChangeLevel.start();
			nEnemiesLeft = 5;
			levelOneDone = false;

		}


		//second level done
		if (nLevel == 2 && nEnemiesLeft == 0 && !timeGameOver.isStarted() && levelTwoDone == false)
		{

			timeGameOver.start();
			levelTwoDone = true;

		}



		if (timeChangeLevel.isStarted())
		{
			App->renderer->camera.y += 4;
		}

		//start level 2
		if (App->renderer->camera.y >= 905 && timeChangeLevel.isStarted())
		{

			timeChangeLevel.stop();
			createPlayerAndEnemies(2);



		}

	
	return UPDATE_CONTINUE;
}