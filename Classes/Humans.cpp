#include "Humans.h"

void GameHumans::Init(const char * pngName, const char * name, float posX, float posY, float Rotation, float Scale,int FM)
{
	// Load Main Sprite
	Humans = Sprite::create(pngName);
	Humans->setAnchorPoint(Vec2(0.5, 0.5));
	Humans->setPosition(posX, posY);
	Humans->setRotation(Rotation);
	Humans->setName(name);
	Humans->setScale(Scale);

	Vector<SpriteFrame*> animFrames;
	if (FM == 1)
	{
		animFrames.reserve(8);
		animFrames.pushBack(SpriteFrame::create("Humans/Man_Right_1.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Man_Right_2.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Man_Right_3.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Man_Right_4.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Man_Left_1.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Man_Left_2.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Man_Left_3.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Man_Left_4.png", Rect(0, 0, 50, 48)));
	}
	else
	{
		animFrames.reserve(8);
		animFrames.pushBack(SpriteFrame::create("Humans/Female_Left_1.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Female_Left_2.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Female_Left_3.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Female_Left_4.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Female_Right_1.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Female_Right_2.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Female_Right_3.png", Rect(0, 0, 50, 48)));
		animFrames.pushBack(SpriteFrame::create("Humans/Female_Right_4.png", Rect(0, 0, 50, 48)));
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animateIdle = Animate::create(animation);
	Humans->runAction(RepeatForever::create(animateIdle));

	/*auto physicsBody = PhysicsBody::createBox(Size(Humans->getContentSize().width, Humans->getContentSize().height),
		PhysicsMaterial(1.0f, 0.0f, 0.0f));

	physicsBody->setDynamic(false);
	physicsBody->setVelocity(Vect(0, -200));
	physicsBody->applyForce(Vect(0, -200));
	physicsBody->applyImpulse(Vect(0, -100));

	Humans->addComponent(physicsBody);*/
	eDir = eStopHuman;
	fSpeed = 0.001f;

}

void GameHumans::MoveChar(EHumanSprite dir)
{
	eDir = dir;
}

void GameHumans::Update(float dt)
{
	if (eDir != EHumanSprite::eStopHuman)
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(eDir, 0.f));
		Humans->runAction(moveEvent);
	}
}

void GameHumans::RotateChar(EHumanSprite dir)
{
	eDir = dir;
}

void GameHumans::AsteroidMove(float posX, float posY)
{
	Humans->stopAllActions();
	//float diffX = posX - Bullets->getPosition().x;
	//float diffY = posY - Bullets->getPosition().y;
	float diffX = posX;
	float diffY = posY;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec * 2);
	Humans->runAction(moveEvent);
}
