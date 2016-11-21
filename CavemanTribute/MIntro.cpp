#include "Globals.h"
#include "Application.h"
#include "MCollision.h"
#include "MRender.h"
#include "MTextures.h"
#include "MIntro.h"
#include "MGameObject.h"
#include "Player.h"
#include "MInput.h"
#include "MScene.h"
#include "Timer.h"
#include "MAudio.h"

MIntro::MIntro(bool start_enabled) : Module(start_enabled)
{
	background = NULL;


}

MIntro::~MIntro()
{

}


bool MIntro::Start()
{

	background = App->Ftextures->Load("Sprites/title.png");
	
	

	App->Faudio->PlayMusic("Audio/Music/intro.ogg");

	return true;
}


bool MIntro::CleanUp()
{

	App->Ftextures->Unload(background);


	return true;
}


update_status MIntro::Update()
{
	
	App->renderer->Blit(background, 0, 0, NULL);
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !timeStart.isStarted())
	{
		timeStart.start();
	}

	if (timeStart.isStarted() && timeStart.getTicks() > 1000)
	{

		this->Disable();
		
		App->FGameObject->Enable();
		App->FCollision->Enable();
		App->scene->Enable();
		timeStart.stop();
	}
		

	return UPDATE_CONTINUE;
}