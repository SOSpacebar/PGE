#include "Buildings.h"
#include "Constants.h"
#include "Character.h"

void GameBuilding::Init(const char * pngName, const char * name, float posX, float posY, float scale)
{
	// Load Main Sprite
	//this->Sprite::create(pngName);
	this->setTexture(pngName);
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(posX, posY);
	this->setName(name);
	this->setScale(scale);
	this->SetActive(true);

	//auto physicsBody = PhysicsBody::createBox(Size(this->getContentSize().width, this->getContentSize().height),
	//	PhysicsMaterial(1.0f, 0.0f, 0.0f));

	//physicsBody->setDynamic(false);
	//physicsBody->setVelocity(Vect(0, -200));
	//physicsBody->applyForce(Vect(0, -200));
	//physicsBody->applyImpulse(Vect(0, -100));
	//physicsBody->setCollisionBitmask(static_cast<int>(CollisionType::ASTEROID)); // This is like tagging a number to the game object, i have set 1 to be for asteroid;
	//physicsBody->setContactTestBitmask(true); //Enables the collision

	//this->addComponent(physicsBody);
	eDir = eStopBuilding;
	//fSpeed = 0.001f;

	this->scheduleUpdate();
}

void GameBuilding::MoveChar(EBuilding dir)
{
	eDir = dir;
}

void GameBuilding::update(float dt)
{
	if (eDir != EBuilding::eStopBuilding)
	{
		//auto moveEvent = MoveBy::create(0.0f, Vec2(eDir, 0.f));
		//this->runAction(moveEvent);
	}

}

void GameBuilding::RotateChar(EBuilding dir)
{
	eDir = dir;
}

void GameBuilding::BuildingMove(float posX, float posY)
{
	this->stopAllActions();
	//float diffX = posX - Bullets->getPosition().x;
	//float diffY = posY - Bullets->getPosition().y;
	float diffX = posX;
	float diffY = posY;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec * 2);
	this->runAction(moveEvent);
}
