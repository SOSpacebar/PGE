#ifndef HUMANS_H
#define HUMANS_H

#include "cocos2d.h"

using namespace cocos2d;

enum EHumanSprite {
	eLeftHuman = -1,
	eStopHuman,
	eRightHuman
};

class GameHumans
{
public:
	void Init(const char * pngName, const char * name, float posX, float posY, float Rotation,float Scale,int FM);
	void MoveChar(EHumanSprite dir);
	void Update(float dt);

	void RotateChar(EHumanSprite dir);

	void AsteroidMove(float posX, float posY);

	Sprite* getSprite(void) { return Humans; }

private:
	EHumanSprite eDir;
	Sprite* Humans;
	float fSpeed;
};

#endif