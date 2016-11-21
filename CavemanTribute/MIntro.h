#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Player.h"

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

	//Audio
	unsigned int introFx;

	//timers
	Timer timeStart;

};