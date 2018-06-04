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
	void Init(const char * pngName, const char * name, float posX, float posY, float Rotation);
	void MoveChar(EAction dir);
	void MoveCharByCoord(float posX, float posY);
	void Update(float dt);
	
	void RotateCharByDir(float Rotation);
	void RotateChar(EAction dir);

	void SetCharAim(Vec2 mouseCursorPs);


	Sprite* getSprite(void) { return mainSprite; }

	float health;

private:
	EAction eDir;
	Sprite* mainSprite;
	float fSpeed;

};

#endif