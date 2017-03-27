#include "Globals.h"
#include "Application.h"
#include "MGameObject.h"
#include "GameObject.h"
#include "Collider.h"
#include "MCollision.h"




MGameObject::MGameObject(){

}

MGameObject::~MGameObject()
{

}

bool MGameObject::Start()
{

	for (auto& it : gameObjects)
	{
		if (it != nullptr)
		{
			it->Start();
		}

	}

	return true;
}


update_status MGameObject::PreUpdate()
{

	for (auto& it : gameObjects)
	{
		if (it != nullptr)
		{
			it->PreUpdate();
		}

	}

	return UPDATE_CONTINUE;
}

update_status MGameObject::Update()
{
	for (auto& it : gameObjects)
	{

		if (it != nullptr)
		{
			if (it->isDead())
			{
				RELEASE(it);
			}
		}


	}

	for (auto& it : gameObjects)
	{
		if (it != nullptr)
		{
			it->Update();
		}
	}

	return UPDATE_CONTINUE;
}

update_status MGameObject::PostUpdate()
{

	for (auto& it : gameObjects)
	{
		if (it != nullptr)
		{
			it->PostUpdate();
		}

	}

	return UPDATE_CONTINUE;
}


bool MGameObject::CleanUp()
{

	for (list<GameObject*>::reverse_iterator it = gameObjects.rbegin(); it != gameObjects.rend(); ++it)
		RELEASE(*it);

	gameObjects.clear();

	return true;
}

void MGameObject::OnCollision(Collider* c1, Collider* c2)
{
	for (auto& it : gameObjects)
	{
		if (it != nullptr)
		{

			if ((it)->colliderBody != nullptr)
			{
				if ((it)->colliderBody->to_delete != true)
				{
					if ((it)->colliderBody == c1)
					{
						it->OnCollision(c1, c2);
					}

				}
			}
		
			
		}	
		
	}
}

void MGameObject::OnCollisionEnter(Collider* c1, Collider* c2)
{
	for (auto& it : gameObjects)
	{
		if (it != nullptr)
		{

			if ((it)->colliderBody != nullptr)
			{
				if ((it)->colliderBody->to_delete != true)
				{
					if ((it)->colliderBody == c1)
					{
						it->OnCollisionEnter(c1, c2);
					}

				}
			}


		}

	}
}

void MGameObject::OnCollisionExit(Collider* c1, Collider* c2)
{
	for (auto& it : gameObjects)
	{
		if (it != nullptr)
		{

			if ((it)->colliderBody != nullptr)
			{
				if ((it)->colliderBody->to_delete != true)
				{
					if ((it)->colliderBody == c1)
					{
						it->OnCollisionExit(c1, c2);
					}

				}
			}


		}

	}
}




GameObject* MGameObject::returnPlayer()
{
	for (list<GameObject*>::reverse_iterator it = gameObjects.rbegin(); it != gameObjects.rend(); ++it)
	{	
		if (*it != nullptr)
		{
			if (!(*it)->isDead())
			{
				if ((*it)->type == PLAYER)
				{
					return  *it;
				}
			}
			
		}
	}

	return NULL;
}

void MGameObject::createGameObject(infoGameObject info, GAMEOBJECT_TYPE type, COLLIDER_TYPE collider_type)
{
	switch (type)
	{
	case PLAYER:
	{
		Player* player = new Player();

		if (collider_type != COLLIDER_NONE)
		{	
			player->colliderBody = App->FCollision->AddCollider({ player->position.x, player->position.y, PLAYER_COLLIDER_BODY_WIDTH,PLAYER_COLLIDER_BODY_HEIGHT}, COLLIDER_PLAYER, this);
		}

		player->Start();

		gameObjects.push_back(player);
	}

		break;

	case BASIC_ENEMY:
	{
		BasicEnemy* enemy = new BasicEnemy(info);

		if (collider_type != COLLIDER_NONE)
		{
			enemy->colliderBody = App->FCollision->AddCollider({ enemy->position.x, enemy->position.y, ENEMY_COLLIDER_BODY_WIDTH_WALKING, ENEMY_COLLIDER_BODY_HEIGHT_WALKING }, COLLIDER_ENEMY, this);
		}

		enemy->Start();

		gameObjects.push_back(enemy);
	}

	break;

	default:
		break;
	}
}
