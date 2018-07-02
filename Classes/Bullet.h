#ifndef _BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

using namespace cocos2d;

enum EBullet {
	eLeftBullet = -1,
	eStopBullet,
	eRightBullet
};

class GameBullet
{
public:
	void Init(const char * pngName, const char * name, float posX, float posY, float Rotation, float mouseX, float mouseY);
	void MoveChar(EBullet dir);
	void MoveCharByCoord(float posX, float posY);
	void Update(float dt);
	
	void RotateChar(EBullet dir);

	void SetShoot(Vec2 mouseCursorPos);
	void BulletMove();

	Sprite* getSprite(void) { return Bullets; }

	float timer = 0;

private:
	EBullet eDir;
	Sprite* Bullets;
	float fSpeed;
	float dirX, dirY;
};

#endif