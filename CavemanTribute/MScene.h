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
	void createLevel();
	void createPlayerAndEnemies(int level);

	//graphics
	SDL_Texture* background = nullptr;
	SDL_Texture* graphicsPlayer = nullptr;
	SDL_Texture* top = nullptr;
	SDL_Rect headIcon;
	SDL_Rect numberZero;
	SDL_Rect numberOne;
	SDL_Rect numberTwo;

	//timers
	Timer timeChangeLevel;
	Timer timeGameOver;
	Timer timeEndGame;

	//variables
	int nEnemiesLeft;
	int nPlayerLives;
	int nLevel;
	bool levelOneDone;
	bool levelTwoDone;
	bool pause;

};