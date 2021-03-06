#ifndef _ASTEROID_H__
#define __ASTEROID_H__

#include "cocos2d.h"
#include "GameObject.h"

using namespace cocos2d;

class GameChar;

enum EAsteroid {
	eLeftAsteroid = -1,
	eStopAsteroid,
	eRightAsteroid
};

class GameAsteroid : public GameObject
{
public:
	void Init(const char * pngName, const char * name, float posX, float posY, float Rotation,float scale, GameChar* player = NULL);
	void MoveChar(EAsteroid dir);
	void update(float dt);

	void RotateChar(EAsteroid dir);

	void AsteroidMove(float posX, float posY);

private:
	EAsteroid eDir;
	float fSpeed;
	GameChar* player;
	ParticleSystem* emitter;
};

#endif