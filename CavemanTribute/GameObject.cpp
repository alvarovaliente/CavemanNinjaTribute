#include "GameObject.h"



GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

bool GameObject::Start()
{
	return true;
}

update_status GameObject::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status GameObject::Update()
{
	return UPDATE_CONTINUE;
}

update_status GameObject::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool GameObject::CleanUp()
{
	return true;

}

bool const GameObject::isDead()
{
	return dead;
}

void GameObject::OnCollision(Collider* c1, Collider* c2)
{

}

void GameObject::roll(DIRECTION dir){}

void GameObject::die(){}

void GameObject::stopRolling(){}

void GameObject::fly(){}


