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
	sky = NULL;
	trees = NULL;
	mountains = NULL;
	facePlayer = NULL;
	lifePlayer = NULL;


	//normal face ui
	faceUInormal.x = 0;
	faceUInormal.y = 0;
	faceUInormal.w = 24;
	faceUInormal.h = 28;

	//life green ui
	lifeGreen.x = 0;
	lifeGreen.y = 0;
	lifeGreen.w = 5;
	lifeGreen.h = 12;

	//life yellow ui

	lifeYellow.x = 5;
	lifeYellow.y = 0;
	lifeYellow.w = 5;
	lifeYellow.h = 12;

	//life red ui
	lifeRed.x = 10;
	lifeRed.y = 0;
	lifeRed.w = 5;
	lifeRed.h = 12;

	//life blank ui
	lifeBlank.x = 15;
	lifeBlank.y = 0;
	lifeBlank.w = 5;
	lifeBlank.h = 12;

}

MScene::~MScene()
{

}


bool MScene::Start()
{

	background = App->Ftextures->Load("Sprites/firstLevel.png");
	sky = App->Ftextures->Load("Sprites/sky.png");
	trees = App->Ftextures->Load("Sprites/trees.png");
	mountains = App->Ftextures->Load("Sprites/mountains.png");
	facePlayer = App->Ftextures->Load("Sprites/gui_portrait.png");
	lifePlayer = App->Ftextures->Load("Sprites/gui_lifebar.png");


	App->Faudio->PlayMusic("Audio/Music/background.ogg", 1.0f);

	infoGameObject infPlayer;

	infPlayer.position = { 30, 160 };

	App->FGameObject->createGameObject(infPlayer, PLAYER, COLLIDER_PLAYER);

	player = dynamic_cast<Player*> (App->FGameObject->returnPlayer());

	player->position.x = infPlayer.position.x;
	player->position.y = infPlayer.position.y;

	//GROUND WALL
	App->FCollision->AddCollider({ 0, SCREEN_HEIGHT - 15, SCREEN_WIDTH, 20 }, COLLIDER_GROUND, this);
	
	pause = false;
	return true;
}




bool MScene::CleanUp()
{

	App->Ftextures->Unload(background);
	App->Ftextures->Unload(sky);
	App->Ftextures->Unload(mountains);
	App->Ftextures->Unload(trees);
	App->Ftextures->Unload(facePlayer);
	App->Ftextures->Unload(lifePlayer);

	return true;
}


update_status MScene::Update()
{
		//SKY
		App->renderer->Blit(sky, 0, 0,NULL, SDL_FLIP_NONE);
		App->renderer->Blit(sky, 256, 0, NULL, SDL_FLIP_NONE);
		App->renderer->Blit(sky, 512, 0, NULL, SDL_FLIP_NONE);
		App->renderer->Blit(sky, 768, 0, NULL, SDL_FLIP_NONE);
		App->renderer->Blit(sky, 1024, 0, NULL, SDL_FLIP_NONE);

		//MOUNTAINS
		App->renderer->Blit(mountains, 0, 0, NULL, SDL_FLIP_NONE);
		App->renderer->Blit(mountains, 256, 0, NULL, SDL_FLIP_NONE);
		App->renderer->Blit(mountains, 513, 0, NULL, SDL_FLIP_NONE);
		App->renderer->Blit(mountains, 768, 0, NULL, SDL_FLIP_NONE);
		App->renderer->Blit(mountains, 1024, 0, NULL, SDL_FLIP_NONE);

		//TREES
		App->renderer->Blit(trees, 0, 0, NULL, SDL_FLIP_NONE);

		//LEVEL SPRITE
		App->renderer->Blit(background, 0, 0, NULL, SDL_FLIP_NONE);

		//FACE
		App->renderer->Blit(facePlayer, 1, 1, &faceUInormal, SDL_FLIP_NONE);

		//LIFE
		for (int i = 0; i < player->life.size();i++)
		{
			if (player->life[i] == 1)
			{ 
				if (player->actualLife >= 15) //green life
				{
					App->renderer->Blit(lifePlayer, 25 + (5 * i), 17, &lifeGreen, SDL_FLIP_NONE);
				}
				else if (player->actualLife < 15 && player->actualLife > 5) //yellow life
				{
					App->renderer->Blit(lifePlayer, 25 + (5 * i), 17, &lifeYellow, SDL_FLIP_NONE);
				}
				else //red life
				{
					App->renderer->Blit(lifePlayer, 25 + (5 * i), 17, &lifeRed, SDL_FLIP_NONE);
				}
			}
			else if (player->life[i] == 0)
			{
				App->renderer->Blit(lifePlayer, 25 + (5 * i), 17, &lifeBlank, SDL_FLIP_NONE);
			}
		}
	
	return UPDATE_CONTINUE;
}