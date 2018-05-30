#ifndef _ASTEROID_H__
#define __ASTEROID_H__

#include "cocos2d.h"

using namespace cocos2d;

enum EAsteroid {
	eLeftAsteroid = -1,
	eStopAsteroid,
	eRightAsteroid
};

class GameAsteroid
{
public:
	void Init(const char * pngName, const char * name, float posX, float posY, float Rotation);
	void MoveChar(EAsteroid dir);
	void Update(float dt);

	void RotateChar(EAsteroid dir);

	void AsteroidMove(float posX, float posY);

	Sprite* getSprite(void) { return Asteroids; }

private:
	EAsteroid eDir;
	Sprite* Asteroids;
	float fSpeed;
};

#endif