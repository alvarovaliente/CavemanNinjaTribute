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
	
	facePlayerPos.x = 0;
	facePlayerPos.y = 0;

	lifePlayerPos.x = 25;
	lifePlayerPos.y = 17;

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
	App->FCollision->AddCollider({ 0, SCREEN_HEIGHT - 15, SCREEN_WIDTH * 5, 20 }, COLLIDER_GROUND, this);


	//DINOSAUR GROUND
	App->FCollision->AddCollider({ 0, 500, SCREEN_WIDTH * 5, 5 }, COLLIDER_GROUND, this);

	//CAMERA MOVE COLLIDER
	moveCameraCollider = App->FCollision->AddCollider({ SCREEN_WIDTH / 2, 0, 2, SCREEN_HEIGHT }, COLLIDER_MOVECAMERA, this);
	
	//STARTLEVEL COLLIDER
	startLevelCollider = App->FCollision->AddCollider({ 0, 0, 2, SCREEN_HEIGHT }, COLLIDER_STARTLEVEL, this);


	infoGameObject inf;
	//ENEMIES
	inf.position = { 200, 184 };

	App->FGameObject->createGameObject(inf, BASIC_ENEMY, COLLIDER_ENEMY);

	

	pause = false;
	return true;
}

void MScene::moveUI()
{

	moveCameraCollider->SetPos(App->scene->moveCameraCollider->rect.x + 1, App->scene->moveCameraCollider->rect.y);
	startLevelCollider->SetPos(App->scene->startLevelCollider->rect.x + 1, App->scene->startLevelCollider->rect.y);
	facePlayerPos.x += 1;
	lifePlayerPos.x += 1;

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
	App->renderer->Blit(sky, 0, 0, NULL, SDL_FLIP_NONE);
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
	App->renderer->Blit(facePlayer, facePlayerPos.x, facePlayerPos.y, &faceUInormal, SDL_FLIP_NONE);

		//LIFE
		for (int i = 0; i < player->life.size();i++)
		{
			if (player->life[i] == 1)
			{ 
				if (player->actualLife >= 15) //green life
				{
					App->renderer->Blit(lifePlayer, lifePlayerPos.x + (5 * i), lifePlayerPos.y, &lifeGreen, SDL_FLIP_NONE);
				}
				else if (player->actualLife < 15 && player->actualLife > 5) //yellow life
				{
					App->renderer->Blit(lifePlayer, lifePlayerPos.x + (5 * i), lifePlayerPos.y, &lifeYellow, SDL_FLIP_NONE);
				}
				else //red life
				{
					App->renderer->Blit(lifePlayer, lifePlayerPos.x + (5 * i), lifePlayerPos.y, &lifeRed, SDL_FLIP_NONE);
				}
			}
			else if (player->life[i] == 0)
			{
				App->renderer->Blit(lifePlayer, lifePlayerPos.x + (5 * i), lifePlayerPos.y, &lifeBlank, SDL_FLIP_NONE);
			}
		}
	
	return UPDATE_CONTINUE;
}