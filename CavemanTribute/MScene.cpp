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
		App->renderer->Blit(sky, 0, 0, NULL);
		App->renderer->Blit(sky, 256, 0, NULL);
		App->renderer->Blit(sky, 512, 0, NULL);
		App->renderer->Blit(sky, 768, 0, NULL);
		App->renderer->Blit(sky, 1024, 0, NULL);

		//MOUNTAINS
		App->renderer->Blit(mountains, 0, 0, NULL);
		App->renderer->Blit(mountains, 256, 0, NULL);
		App->renderer->Blit(mountains, 513, 0, NULL);
		App->renderer->Blit(mountains, 768, 0, NULL);
		App->renderer->Blit(mountains, 1024, 0, NULL);

		//TREES
		App->renderer->Blit(trees, 0, 0, NULL);

		//LEVEL SPRITE
		App->renderer->Blit(background, 0, 0, NULL);

		//FACE
		App->renderer->Blit(facePlayer, 1, 1, &faceUInormal);

		//LIFE
		for (int i = 0; i < App->FPlayer->life.size();i++)
		{
			if (App->FPlayer->life[i] == 1)
			{ 
				if (App->FPlayer->actualLife >= 15) //green life
				{
					App->renderer->Blit(lifePlayer, 25 + (5 * i), 17, &lifeGreen);
				}
				else if (App->FPlayer->actualLife < 15 && App->FPlayer->actualLife > 5) //yellow life
				{
					App->renderer->Blit(lifePlayer, 25 + (5 * i), 17, &lifeYellow);
				}
				else //red life
				{
					App->renderer->Blit(lifePlayer, 25 + (5 * i), 17, &lifeRed);
				}
			}
			else if (App->FPlayer->life[i] == 0)
			{
				App->renderer->Blit(lifePlayer, 25 + (5 * i), 17, &lifeBlank);
			}
		}
	
	return UPDATE_CONTINUE;
}