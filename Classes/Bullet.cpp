#include "Bullet.h"
#include "AudioManager.h"
#include "Constants.h"

void GameBullet::Init(const char * pngName, const char * name, float posX, float posY,float Rotation, float mouseX, float mouseY)
{
	// Load Main Sprite
	Bullets = Sprite::create(pngName);
	Bullets->setAnchorPoint(Vec2(0.5, 0.5));
	Bullets->setPosition(posX, posY);
	Bullets->setRotation(Rotation);
	Bullets->setName(name);

	auto physicsBody = PhysicsBody::createBox(Size(Bullets->getContentSize().width, Bullets->getContentSize().height),
		PhysicsMaterial(1.0f,0.0f,0.0f));
	
	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(static_cast<int>(CollisionType::ROCKET)); // This is like tagging a number to the game object, i have set 2 to be for rocket;
	physicsBody->setContactTestBitmask(true); //Enables the collision

	Bullets->addComponent(physicsBody);
	eDir = eStopBullet;
	fSpeed = 0.001f;

	dirX = mouseX;
	dirY = mouseY;

	AudioManager::GetInstance()->SFXPlay("SFX_Rocket");
}

void GameBullet::MoveChar(EBullet dir)
{
	eDir = dir;
}

void GameBullet::MoveCharByCoord(float posX, float posY)
{
	Bullets->stopAllActions();
	float diffX = posX - Bullets->getPosition().x;
	float diffY = posY - Bullets->getPosition().y;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec);
	Bullets->runAction(moveEvent);
}

void GameBullet::Update(float dt)
{
	if (eDir != EBullet::eStopBullet)
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(eDir, 0.f));
		Bullets->runAction(moveEvent);
	}
}


void GameBullet::RotateChar(EBullet dir)
{
	eDir = dir;
}

void GameBullet::SetShoot(Vec2 mouseCursorPos)
{
	Vec2 dir;
	dir = mouseCursorPos - Bullets->getPosition();
	dir.normalize();
	float angle = atan2(dir.y, dir.x);
	angle = CC_RADIANS_TO_DEGREES(angle);
	Bullets->setRotation(-angle);
}

void GameBullet::BulletMove()
{
	Bullets->stopAllActions();
	//float diffX = posX - Bullets->getPosition().x;
	//float diffY = posY - Bullets->getPosition().y;
	float diffX = dirX;
	float diffY = dirY;
	Vec2 vec = Vec2(diffX, diffY);
	// auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec * 10);
	auto moveEvent = MoveBy::create(5, vec.getNormalized() * 3000);

	Bullets->runAction(moveEvent);
}

