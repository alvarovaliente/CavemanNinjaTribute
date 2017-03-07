#include "Collider.h"
#include "SDL/include/SDL.h"
#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"


Collider::Collider(SDL_Rect rectangle, COLLIDER_TYPE typeof, Module* callbackM)
{
	rect = rectangle;
	type = typeof;
	callback = callbackM;
	active = true;
}

Collider::~Collider()
{

}

void Collider::SetPos(float x, float y)
{
		rect.x = (int) x;
		rect.y = (int) y;
}

bool const Collider::CheckCollision(SDL_Rect r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}

bool Collider::existInColliding(Collider* c)
{
	if (colliding.size() > 0)
	{

	
		for (list<Collider*>::iterator it = colliding.begin(); it != colliding.end();)
		{
			if (*it == c)
			{
				return true;
			}
			else
				++it;
		}
	}

	return false;
}

bool Collider::addNewCollider(Collider * c)
{

	/*if (!existInColliding(c))
	{
		colliding.push_back(c);
		return true;
	}
	else
	{
		return false;
	}*/

	for (list<Collider*>::iterator it = colliding.begin(); it != colliding.end();)
	{
		if (*it == c)
		{
			return false;
		}
		else
			++it;
	}
	
	colliding.push_back(c);

	return true;
}

bool Collider::removeCollider(Collider* c)
{
	if (colliding.size() > 0)
	{ 
		for (list<Collider*>::iterator it = colliding.begin(); it != colliding.end();)
		{
			if (*it == c)
			{
			
				//colliding.remove(*it);
				colliding.erase(it);
				return true;
			}
			else
				++it;
		}
	}
	return false;
}