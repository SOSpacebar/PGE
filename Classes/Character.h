#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

using namespace cocos2d;

enum EAction {
	eLeft = -1,
	eStop,
	eRight
};

class GameChar
{
public:
	void Init(const char * pngName, const char * name, float posX, float posY);
	void MoveChar(EAction dir);
	void StopChar();
	void MoveCharByCoord(float posX, float posY);
	void Update(float dt);

	Sprite* getSprite(void) { return mainSprite; }

private:
	EAction eDir;
	Sprite* mainSprite;
	float fSpeed;
};



#endif