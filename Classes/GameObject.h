#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "cocos2d.h"

using namespace cocos2d;

class GameObject : public Sprite
{
public:
	GameObject();
	~GameObject();
	GameObject(const GameObject &gameObject);
	void operator= (const GameObject &gameObject);
	void SetActive(bool b);
private:
	bool isActive;
};



#endif // !GAMEOBJECT_H


