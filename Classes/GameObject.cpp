#include "GameObject.h"
#include "Constants.h"

GameObject::GameObject() : isActive(false)
{
	Constant::GetInstance()->SetGameObjectCount(Constant::GetInstance()->GetGameObjectCount() + 1);
	log("Add GameObject Count %d", Constant::GetInstance()->GetGameObjectCount());
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