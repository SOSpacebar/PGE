#include "Asteroid.h"
#include "Constants.h"
#include "Character.h"

void GameAsteroid::Init(const char * pngName, const char * name, float posX, float posY, float rotation, GameChar* player)
{
	// Load Main Sprite
	//this->Sprite::create(pngName);
	this->setTexture(pngName);
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(posX, posY);
	this->setRotation(rotation);
	this->setName(name);
	this->SetActive(true);

	auto physicsBody = PhysicsBody::createBox(Size(this->getContentSize().width, this->getContentSize().height),
		PhysicsMaterial(1.0f, 0.0f, 0.0f));

	physicsBody->setDynamic(false);
	physicsBody->setVelocity(Vect(0, -200));
	physicsBody->applyForce(Vect(0, -200));
	physicsBody->applyImpulse(Vect(0, -100));
	physicsBody->setCollisionBitmask(static_cast<int>(CollisionType::ASTEROID)); // This is like tagging a number to the game object, i have set 1 to be for asteroid;
	physicsBody->setContactTestBitmask(true); //Enables the collision

	this->addComponent(physicsBody);
	eDir = eStopAsteroid;
	fSpeed = 0.001f;

	this->player = player;

	emitter = ParticleGalaxy::create();
	emitter->retain();
	emitter->setPositionType(ParticleSystem::PositionType::RELATIVE);
	emitter->setPosition(this->getPosition());
	addChild(emitter, 10);

	//this->scheduleUpdate();
}

void GameAsteroid::MoveChar(EAsteroid dir)
{
	eDir = dir;
}

void GameAsteroid::update(float dt)
{
	if (eDir != EAsteroid::eStopAsteroid)
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(eDir, 0.f));
		this->runAction(moveEvent);
	}

	if (this->getPosition().y < 0)
	{
		this->removeFromParentAndCleanup(true);
		float hp = Constant::GetInstance()->GetHealth();
		Constant::GetInstance()->SetHealth((Constant::GetInstance()->GetHealth() - 5.f));
		Constant::GetInstance()->SetGameObjectCount(Constant::GetInstance()->GetGameObjectCount() - 1);
		log("Delete GameObject Count %d", Constant::GetInstance()->GetGameObjectCount());
	}
}

void GameAsteroid::RotateChar(EAsteroid dir)
{
	eDir = dir;
}

void GameAsteroid::AsteroidMove(float posX, float posY)
{
	this->stopAllActions();
	//float diffX = posX - Bullets->getPosition().x;
	//float diffY = posY - Bullets->getPosition().y;


	float diffX = posX;
	float diffY = posY;
	Vec2 vec = Vec2(diffX, diffY);

	emitter->setPosition(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec * 2);
	this->runAction(moveEvent);
}
