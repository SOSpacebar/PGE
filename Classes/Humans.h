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
	void Init(const char * pngName, const char * name, float posX, float posY, float rotation,float scale,int fM, int playingSize);
	void MoveChar(EHumanSprite dir);
	void Update(float dt);

	void stop();                                                                              

	void RotateChar(EHumanSprite dir);

	void HumanMove(float posX, float posY);

	Sprite* getSprite(void) { return humans; }

private:
	EHumanSprite eDir;
	Sprite* humans;
	float fSpeed;
	int fMale;
	int playingSizeWidth;
	bool left;
	bool a = true;
};

#endif