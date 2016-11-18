#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class Collider;

class MGameOver : public Module
{
public:

	MGameOver(bool start_enabled = true);
	~MGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;

	unsigned int gameOverFx;

};