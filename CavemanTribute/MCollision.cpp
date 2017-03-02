#include "Globals.h"
#include "Application.h"
#include "MInput.h"
#include "MRender.h"
#include "MCollision.h"
#include "Collider.h"
#include "SDL/include/SDL.h"


using namespace std;


MCollision::MCollision() : Module()
{
	debug = false;

	// Matrix is game specific, change it to adapt to your own needs
	// ... think of moving this outside ModuleCollision
	matrix[COLLIDER_GROUND][COLLIDER_GROUND] = false;
	matrix[COLLIDER_GROUND][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_GROUND][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_GROUND][COLLIDER_STARTLEVEL] = false;
	matrix[COLLIDER_STARTLEVEL][COLLIDER_GROUND] = false;
	matrix[COLLIDER_MOVECAMERA][COLLIDER_GROUND] = false;
	matrix[COLLIDER_GROUND][COLLIDER_MOVECAMERA] = false;

	matrix[COLLIDER_MOVECAMERA][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_MOVECAMERA] = true;

	matrix[COLLIDER_STARTLEVEL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_STARTLEVEL] = true;

	

	matrix[COLLIDER_PLAYER][COLLIDER_GROUND] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;


	matrix[COLLIDER_ENEMY][COLLIDER_GROUND] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_STONEAXE] = true;
	

	matrix[COLLIDER_STONEAXE][COLLIDER_GROUND] = true;
	matrix[COLLIDER_STONEAXE][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_STONEAXE][COLLIDER_STONEAXE] = false;
	matrix[COLLIDER_GROUND][COLLIDER_STONEAXE] = true;
	matrix[COLLIDER_STONEAXE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_STONEAXE] = false;

	
}

// Destructor
MCollision::~MCollision()
{}



update_status MCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status MCollision::Update()
{

	Collider* c1;
	Collider* c2;

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		c1 = *it;

		for (list<Collider*>::iterator it2 = ++it; it2 != colliders.end(); ++it2)
		{
			c2 = *it2;

		
			if (c1->CheckCollision(c2->rect) == true)
			{
				
					if (matrix[c1->type][c2->type] && c1->callback)
					{
						if (c1->addNewCollider(c2)) //new collision
						{
							c1->callback->OnCollisionEnter(c1, c2);
						}
						else //they still colliding
						{
							c1->callback->OnCollision(c1, c2);
						}
					}

					if (matrix[c2->type][c1->type] && c2->callback)
					{
						if (c2->addNewCollider(c1))
						{
							c2->callback->OnCollisionEnter(c2, c1);
						}
						else
						{
							c2->callback->OnCollision(c2, c1);
						}
					}
						
			}
			else
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollisionExit(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollisionExit(c2, c1);
			}
		

				/*if (c1->CheckCollision(c2->rect) == true)
				{
					if (matrix[c1->type][c2->type] && c1->callback)
						c1->callback->OnCollision(c1, c2);

					if (matrix[c2->type][c1->type] && c2->callback)
						c2->callback->OnCollision(c2, c1);
				}*/


		}
	}

	return UPDATE_CONTINUE;
	
}

// Called before render is available
update_status MCollision::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		debug = !debug;

	if (debug == true)
	{
		for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		{
			Collider* col = *it;
			Uint8 alpha = 100;

			switch (col->type)
			{
			case COLLIDER_NONE:
				App->renderer->DrawQuad(col->rect, 255, 255, 255, alpha);
				break;
			case COLLIDER_GROUND:
				App->renderer->DrawQuad(col->rect, 0, 0, 255, alpha);
				break;
			
			case COLLIDER_PLAYER:
				App->renderer->DrawQuad(col->rect, 0, 255, 0, alpha);
				break;
			case COLLIDER_FOOT:
				App->renderer->DrawQuad(col->rect, 255, 0, 246, alpha);
				break;
			case COLLIDER_ENEMY:
				App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
				break;
			case COLLIDER_STARTLEVEL:
				App->renderer->DrawQuad(col->rect, 255, 162, 0, alpha);
				break;

			case COLLIDER_MOVECAMERA:
				App->renderer->DrawQuad(col->rect, 255, 162, 0, alpha);
				break;

			case COLLIDER_STONEAXE:
				App->renderer->DrawQuad(col->rect, 0, 255, 0, alpha);
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool MCollision::CleanUp()
{

	for (list<Collider*>::reverse_iterator it = colliders.rbegin(); it != colliders.rend(); ++it)
		RELEASE(*it);


	colliders.clear();
	return true;
}

Collider* MCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = new Collider(rect, type, callback);
	colliders.push_back(ret);
	return ret;
}


// -----------------------------------------------------

