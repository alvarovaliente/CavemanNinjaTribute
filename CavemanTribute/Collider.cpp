#include "Collider.h"
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