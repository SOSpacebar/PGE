#ifndef _BUILDINGS_H__
#define _BUILDINGS_H__

#include "cocos2d.h"
#include "GameObject.h"

using namespace cocos2d;

enum EBuilding {
	eLeftBuilding = -1,
	eStopBuilding,
	eRightBuilding
};

class GameBuilding : public GameObject
{
public:
	void Init(const char * pngName, const char * name, float posX, float posY, float scale);
	void MoveChar(EBuilding dir);
	void update(float dt);

	void RotateChar(EBuilding dir);

	void BuildingMove(float posX, float posY);

private:
	EBuilding eDir;
	float fSpeed;
};

#endif