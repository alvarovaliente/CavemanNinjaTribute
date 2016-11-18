#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class MInput;
class MWindow;
class MRender;
class MTextures;
class MAudio;
class MGameObject;
class MCollision;
class MParticle;
class MScene;
class MIntro;
class MGameOver;


class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	
	bool CleanUp();

public:

	MInput* input;
	MWindow* window;
	MRender* renderer;
	MTextures *Ftextures;
	MAudio *Faudio;
	MGameObject *FGameObject;
	MCollision *FCollision;
	MParticle *FParticle;
	MScene *scene;
	MIntro *intro;
	MGameOver *gameover;
	
private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__