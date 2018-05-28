#include "Character.h"

void GameChar::Init(const char * pngName, const char * name, float posX, float posY,float Rotation)
{
	// Load Main Sprite
	mainSprite = Sprite::create(pngName);
	mainSprite->setAnchorPoint(Vec2(0.5, 0.5));
	mainSprite->setPosition(posX, posY);
	mainSprite->setRotation(Rotation);
	mainSprite->setName(name);

	auto physicsBody = PhysicsBody::createBox(Size(mainSprite->getContentSize().width, mainSprite->getContentSize().height),
		PhysicsMaterial(1.0f,0.0f,0.0f));
	
	physicsBody->setDynamic(false);

	mainSprite->addComponent(physicsBody);
	eDir = eStop;
	fSpeed = 0.01f;
}

void GameChar::MoveChar(EAction dir)
{
	eDir = dir;
}

void GameChar::MoveCharByCoord(float posX, float posY)
{
	mainSprite->stopAllActions();
	float diffX = posX - mainSprite->getPosition().x;
	float diffY = posY - mainSprite->getPosition().y;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec);
	mainSprite->runAction(moveEvent);
}

void GameChar::Update(float)
{
	if (eDir != EAction::eStop)
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(eDir, 0.f));
		mainSprite->runAction(moveEvent);
	}
}

void GameChar::RotateCharByDir(float Rotation)
{
	/*mainSprite->stopAllActions();
	float rotate = mainSprite->getRotation();
	auto rotateEvent = RotateBy::create(2, Vec3(0,0,90));
	mainSprite->runAction(rotateEvent);*/
}

void GameChar::RotateChar(EAction dir)
{
	eDir = dir;
}

void GameChar::SetCharAim(Vec2 mouseCursorPos)
{
	Vec2 dir;
	dir = mouseCursorPos - mainSprite->getPosition();
	dir.normalize();
	float angle = atan2(dir.y, dir.x);
	angle = CC_RADIANS_TO_DEGREES(angle) - 90;
	mainSprite->setRotation(-angle);
}


