#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Point.h"
#include "Globals.h"
#include "Module.h"
//#include "MGameObject.h"

using namespace std;

enum GAMEOBJECT_TYPE
{
	PLAYER = 1,
};


struct infoGameObject
{
	iPoint position;
};



class GameObject : public Module
{

public:

	//methods
	GameObject();
	virtual ~GameObject();

	virtual bool Start();
	virtual update_status PreUpdate();
	virtual update_status Update();
	virtual update_status PostUpdate();
	virtual bool CleanUp();
	virtual const bool isDead();
	virtual void OnCollision(Collider* c1, Collider* c2);

	//variables
	iPoint position;
	bool dead;
	GAMEOBJECT_TYPE type;
	Collider* colliderBody = nullptr;

};

#endif