#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameChar
{
public:
	void Init(const char * pngName, const char * name, float posX, float posY, float rotation);
	//void MoveChar(EAction dir);
	void MoveCharByCoord(float posX, float posY);
	void Update(float dt);
	
	void RotateCharByDir(float Rotation);
	void RotateCharByDirRight();
	void RotateCharByDirLeft();
	//void RotateChar(EAction dir);

	void SetCharAim(Vec2 mouseCursorPs);
	void StopRotation();

	Sprite* getSprite(void) { return mainSprite; }

	float health;

private:
	//EAction eDir;
	Vec3 rotateDir;
	Sprite* mainSprite;
	float fSpeed;

};

#endif