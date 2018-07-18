#include "GameObject.h"

GameObject::GameObject() : isActive(false)
{
}

GameObject::~GameObject()
{
}

GameObject::GameObject(const GameObject & gameObject) : isActive(false)
{
}

void GameObject::operator=(const GameObject & gameObject)
{
	
}

void GameObject::SetActive(bool b)
{
	isActive = b;
}