#ifndef __MCOLLISION_H__
#define __MCOLLISION_H__

#include "Module.h"
#include <list>
#include "Collider.h"



class MCollision : public Module
{
public:

	//methods
	MCollision();
	~MCollision();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = NULL);

private:

	//variables
	std::list<Collider*> colliders;
	std::list<Collider*> colliding;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug;
};

#endif // __MODULECOLLISION_H__