#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Player.h"



class Collider;

class MScene : public Module
{
public:

	//methods
	MScene(bool start_enabled = true);
	~MScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	void moveUI();


	//graphics
	SDL_Texture* background = nullptr;
	SDL_Texture* graphicsPlayer = nullptr;
	SDL_Texture* sky = nullptr;
	SDL_Texture* mountains = nullptr;
	SDL_Texture* trees = nullptr;
	SDL_Texture* facePlayer = nullptr;
	SDL_Texture* lifePlayer = nullptr;

	SDL_Rect faceUInormal;

	SDL_Rect lifeGreen;
	SDL_Rect lifeYellow;
	SDL_Rect lifeRed;
	SDL_Rect lifeBlank;

	Collider* moveCameraCollider = nullptr;
	Collider* startLevelCollider = nullptr;


	iPoint facePlayerPos;
	iPoint lifePlayerPos;

	//Player
	Player *player;

	bool pause;

};