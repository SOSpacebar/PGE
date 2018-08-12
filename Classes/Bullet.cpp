#include "Bullet.h"
#include "AudioManager.h"
#include "Constants.h"

void GameBullet::Init(const char * pngName, const char * name, float posX, float posY,float Rotation, float mouseX, float mouseY)
{
	// Load Main Sprite
	//this = Sprite::create(pngName);
	this->setTexture(pngName);
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(posX, posY);
	this->setRotation(Rotation);
	this->setName(name);
	this->SetActive(true);

	auto physicsBody = PhysicsBody::createBox(Size(this->getContentSize().width, this->getContentSize().height),
		PhysicsMaterial(1.0f,0.0f,0.0f));
	
	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(static_cast<int>(CollisionType::ROCKET)); // This is like tagging a number to the game object, i have set 2 to be for rocket;
	physicsBody->setContactTestBitmask(true); //Enables the collision

	this->addComponent(physicsBody);
	eDir = eStopBullet;
	fSpeed = 0.001f;

	rotation = Rotation;
	dirX = mouseX;
	dirY = mouseY;

	AudioManager::GetInstance()->SFXPlay("SFX_Rocket");

	//this->scheduleUpdate();
}

void GameBullet::Init(const char * pngName, const char * name, float posX, float posY, float Rotation)
{
	this->setTexture(pngName);
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(posX, posY);
	this->setRotation(Rotation);
	this->setName(name);
	this->SetActive(true);

	auto physicsBody = PhysicsBody::createBox(Size(this->getContentSize().width, this->getContentSize().height),
		PhysicsMaterial(1.0f, 0.0f, 0.0f));

	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(static_cast<int>(CollisionType::ROCKET)); // This is like tagging a number to the game object, i have set 2 to be for rocket;
	physicsBody->setContactTestBitmask(true); //Enables the collision

	this->addComponent(physicsBody);
	/*eDir = eStopBullet;
	fSpeed = 0.001f;*/

	AudioManager::GetInstance()->SFXPlay("SFX_Rocket");

	//this->scheduleUpdate();
}

void GameBullet::MoveChar(EBullet dir)
{
	eDir = dir;
}

void GameBullet::MoveCharByCoord(float posX, float posY)
{
	this->stopAllActions();
	float diffX = posX - this->getPosition().x;
	float diffY = posY - this->getPosition().y;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec);
	this->runAction(moveEvent);
}

void GameBullet::update(float dt)
{
	//if (eDir != EBullet::eStopBullet)
	//{
	//	auto moveEvent = MoveBy::create(0.0f, Vec2(eDir, 0.f));
	//	this->runAction(moveEvent);
	//}

	if (this->getPosition().x > Constant::GetInstance()->GetVisableSize().width || 
		this->getPosition().x < 0 ||
		this->getPosition().y > Constant::GetInstance()->GetVisableSize().height ||
		this->getPosition().y < 0)
	{
		this->removeFromParentAndCleanup(true);
		Constant::GetInstance()->SetGameObjectCount(Constant::GetInstance()->GetGameObjectCount() - 1);
		log("Delete GameObject Count %d", Constant::GetInstance()->GetGameObjectCount());
	}
}


void GameBullet::RotateChar(EBullet dir)
{
	eDir = dir;
}

void GameBullet::SetShoot(Vec2 mouseCursorPos)
{
	Vec2 dir;
	dir = mouseCursorPos - this->getPosition();
	dir.normalize();
	float angle = atan2(dir.y, dir.x);
	angle = CC_RADIANS_TO_DEGREES(angle);
	if(Constant::GetInstance()->GetAttackLevel() != GameStats::SPLITROUND)
		this->setRotation(-angle);
	else
		this->setRotation(-angle+rotation);
}

void GameBullet::BulletMove()
{
	//this->stopAllActions();
	//float diffX = posX - Bullets->getPosition().x;
	//float diffY = posY - Bullets->getPosition().y;
	/*float diffX = dirX;
	float diffY = dirY;
	Vec2 vec = Vec2(diffX, diffY);*/
	// auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec * 10);
	Vec3 targetPos = getPosition3D();

	Vec3 dir = Vec3(
		CC_RADIANS_TO_DEGREES(cosf(CC_DEGREES_TO_RADIANS(abs(getRotation())))), 
		CC_RADIANS_TO_DEGREES(sinf(CC_DEGREES_TO_RADIANS(abs(getRotation())))), 0);
	dir.normalize();
	targetPos = targetPos + dir * 3000;
	CCLOG("%f,%f,%f", dir.x, dir.y, dir.z);
	auto moveEvent = MoveTo::create(10, targetPos);

	//Bullets->runAction(moveEvent);
	this->runAction(moveEvent);
}

