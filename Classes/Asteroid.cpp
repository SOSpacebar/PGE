#include "Asteroid.h"

void GameAsteroid::Init(const char * pngName, const char * name, float posX, float posY, float Rotation)
{
	// Load Main Sprite
	Asteroids = Sprite::create(pngName);
	Asteroids->setAnchorPoint(Vec2(0.5, 0.5));
	Asteroids->setPosition(posX, posY);
	Asteroids->setRotation(Rotation);
	Asteroids->setName(name);

	auto physicsBody = PhysicsBody::createBox(Size(Asteroids->getContentSize().width, Asteroids->getContentSize().height),
		PhysicsMaterial(1.0f, 0.0f, 0.0f));

	physicsBody->setDynamic(false);
	physicsBody->setVelocity(Vect(0, -200));
	physicsBody->applyForce(Vect(0, -200));
	physicsBody->applyImpulse(Vect(0, -100));

	Asteroids->addComponent(physicsBody);
	eDir = eStopAsteroid;
	fSpeed = 0.001f;

}

void GameAsteroid::MoveChar(EAsteroid dir)
{
	eDir = dir;
}

void GameAsteroid::Update(float dt)
{
	if (eDir != EAsteroid::eStopAsteroid)
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(eDir, 0.f));
		Asteroids->runAction(moveEvent);
	}

	//RotateChar(EAsteroid::eRightAsteroid);
	/*int loopSize = std::ceil(visibleSize.width / sprite->getContentSize().width);
	int sX = 0;
	int sY = (visibleSize.height - playingSize.height) - sprite->getContentSize().height;

	for (size_t i = 0; i < loopSize; ++i)
	{
		auto newNode = Sprite::createWithSpriteFrame(sprite->getSpriteFrame());
		newNode->setAnchorPoint(Vec2::ZERO);
		newNode->setPosition(sX, sY);
		sX += newNode->getContentSize().width;

		auto physicsBody = PhysicsBody::createBox(Size(newNode->getContentSize().width, newNode->getContentSize().height),
			PhysicsMaterial(1.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		newNode->addComponent(physicsBody);

		nodeItems->addChild(newNode, 0);
	}*/
}

void GameAsteroid::RotateChar(EAsteroid dir)
{
	eDir = dir;
}

void GameAsteroid::AsteroidMove(float posX, float posY)
{
	Asteroids->stopAllActions();
	//float diffX = posX - Bullets->getPosition().x;
	//float diffY = posY - Bullets->getPosition().y;
	float diffX = posX;
	float diffY = posY;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec * 2);
	Asteroids->runAction(moveEvent);
}
