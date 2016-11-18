#include "Application.h"
#include "MInput.h"
#include "MRender.h"
#include "MWindow.h"
#include "MTextures.h"
#include "MAudio.h"
#include "MGameObject.h"
#include "MCollision.h"
#include "MParticle.h"
#include "MScene.h"
#include "MIntro.h"
#include "MGameOver.h"

using namespace std;

Application::Application()
{
	modules.push_back(input = new MInput());
	modules.push_back(window = new MWindow());

	modules.push_back(Ftextures = new MTextures());

	modules.push_back(Faudio = new MAudio());

	modules.push_back(intro = new MIntro(true));
	modules.push_back(scene = new MScene(false));
	modules.push_back(gameover = new MGameOver(false));
	modules.push_back(FGameObject = new MGameObject());
	modules.push_back(FParticle = new MParticle());

	

	modules.push_back(FCollision = new MCollision());

	modules.push_back(renderer = new MRender());

}

Application::~Application()
{
	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}


	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();

	return ret;
}


