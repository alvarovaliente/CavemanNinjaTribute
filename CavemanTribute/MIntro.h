#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Player.h"


class Collider;

class MIntro : public Module
{
public:

	MIntro(bool start_enabled = true);
	~MIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

	//graphics
	SDL_Texture* background = nullptr;
	//SDL_Texture* start = nullptr;

	//timers
	Timer timeStart;

	unsigned int introFx;
	//unsigned int startFx;

};