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
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SOFT_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_HARD_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLATFORM] = false;


	matrix[COLLIDER_PLATFORM][COLLIDER_WALL] = false;

	

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SOFT_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_HARD_SHOT] = false;
	
	matrix[COLLIDER_PLAYER][COLLIDER_PLATFORM_BORDER_LEFT_SPEC] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLATFORM_BORDER_RIGHT_SPEC] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_POTION_RED] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POTION_BLUE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POTION_YELLOW] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_PLATFORM] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLATFORM_SPEC] = false;

	matrix[COLLIDER_FOOT][COLLIDER_PLATFORM] = true;
	matrix[COLLIDER_FOOT][COLLIDER_PLATFORM_SPEC] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SOFT_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_HARD_SHOT] = true;
	
	matrix[COLLIDER_ENEMY][COLLIDER_PLATFORM_BORDER_LEFT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLATFORM_BORDER_RIGHT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLATFORM_BORDER_LEFT_SPEC] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLATFORM_BORDER_RIGHT_SPEC] = true;
	

	matrix[COLLIDER_PLAYER_SOFT_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SOFT_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SOFT_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SOFT_SHOT][COLLIDER_PLAYER_SOFT_SHOT] = false;

	matrix[COLLIDER_PLAYER_HARD_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_HARD_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_HARD_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_HARD_SHOT][COLLIDER_PLAYER_HARD_SHOT] = false;


	

	
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
						c1->callback->OnCollision(c1, c2);

					if (matrix[c2->type][c1->type] && c2->callback)
						c2->callback->OnCollision(c2, c1);
				}
			

			


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
			case COLLIDER_WALL:
				App->renderer->DrawQuad(col->rect, 0, 0, 255, alpha);
				break;
			case COLLIDER_PLATFORM:
				App->renderer->DrawQuad(col->rect, 1,234, 255, alpha);
				break;
			case COLLIDER_PLATFORM_BORDER_LEFT:
				App->renderer->DrawQuad(col->rect, 1, 284, 255, alpha);
				break;
			case COLLIDER_PLATFORM_BORDER_RIGHT:
				App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
				break;
			case COLLIDER_PLATFORM_BORDER_RIGHT_SPEC:
				App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
				break;
			case COLLIDER_PLATFORM_BORDER_LEFT_SPEC:
				App->renderer->DrawQuad(col->rect, 1, 284, 255, alpha);
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
			case COLLIDER_PLAYER_SOFT_SHOT:
				App->renderer->DrawQuad(col->rect, 255, 255, 0, alpha);
				break;

			case COLLIDER_PLAYER_HARD_SHOT:
				App->renderer->DrawQuad(col->rect, 255, 255, 0, alpha);
				break;
		
			case COLLIDER_POTION_RED:
				App->renderer->DrawQuad(col->rect, 255, 162, 0, alpha);
				break;

			case COLLIDER_POTION_BLUE:
				App->renderer->DrawQuad(col->rect, 255, 162, 0, alpha);
				break;

			case COLLIDER_POTION_YELLOW:
				App->renderer->DrawQuad(col->rect, 255, 162, 0, alpha);
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

