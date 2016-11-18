

#ifndef __MGAMEOBJECT_H__
#define __MGAMEOBJECT_H__

#include "Module.h"
#include "Globals.h"
#include "Collider.h"
#include "Point.h"
#include "GameObject.h"
#include <list>




struct infoGameObject
{
	iPoint position;
};


class GameObject;

class MGameObject : public Module
{
public:


	MGameObject();
	~MGameObject();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	GameObject* Owner(Collider const *collider);
	GameObject* returnPlayer();
	void createGameObject(infoGameObject info, GAMEOBJECT_TYPE type, COLLIDER_TYPE collider_type);
	void OnCollision(Collider* c1, Collider* c2);

private:

	std::list<GameObject*> gameObjects;


};

#endif // __MGAMEOBJECT_H__