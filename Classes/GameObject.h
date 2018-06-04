#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "cocos2d.h"

using namespace cocos2d;

class GameObject : public Sprite
{
public:
	void SetActive(bool b);
private:
	bool isActive;
};



#endif // !GAMEOBJECT_H


