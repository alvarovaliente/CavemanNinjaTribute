#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Point.h"
#include "Globals.h"
//#include "MGameObject.h"

using namespace std;

enum GAMEOBJECT_TYPE
{
	PLAYER = 1,
	ENEMY_ROSEGOBLIN,
	ENEMY_YELLOWMONKEY,
	RED_POTION,
	BLUE_POTION,
	YELLOW_POTION
};

enum ENEMY_STATUS
{
	ENEMY_IDLE_LEFT = 1,
	ENEMY_IDLE_RIGHT,

	ENEMY_WALKING_LEFT,
	ENEMY_WALKING_RIGHT,

	ENEMY_TRAPPED,
	ENEMY_SNOWBALL,
	ENEMY_SNOWBALL_BEING_PUSHED,
	ENEMY_ROLLING,

	ENEMY_JUMPING_LEFT,
	ENEMY_JUMPING_RIGHT,
	ENEMY_DYING



};


enum DIRECTION
{
	LEFT = 1,
	RIGHT
};


class Collider;


class GameObject
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
	virtual void roll(DIRECTION dir);
	virtual void die();
	virtual void stopRolling();
	virtual void fly();
	virtual void OnCollision(Collider* c1, Collider* c2);

	//variables
	iPoint position;
	bool dead;
	GameObject *link = nullptr;
	GAMEOBJECT_TYPE type;
	Collider* colliderBody = nullptr;
	Collider* colliderFoot = nullptr;

};

#endif