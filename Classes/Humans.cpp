#include "Humans.h"

void GameHumans::Init(const char * pngName, const char * name, float posX, float posY, float rotation, float scale,int fM)
{
	// Load Main Sprite
	humans = Sprite::create(pngName);
	humans->setAnchorPoint(Vec2(0.5, 0.5));
	humans->setPosition(posX, posY);
	humans->setRotation(rotation);
	humans->setName(name);
	humans->setScale(scale);

	stop();
	//Vector<SpriteFrame*> animFrames;
	

	fMale = fM;

	auto moveEvent = MoveBy::create(5, Vec2(500, 0));
	moveEvent->setTag(1);
	humans->runAction(moveEvent);
	

	//auto delay = DelayTime::create(5.0f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), nullptr);
	humans->runAction(RepeatForever::create(sequence));

	/*auto physicsBody = PhysicsBody::createBox(Size(Humans->getContentSize().width, Humans->getContentSize().height),
		PhysicsMaterial(1.0f, 0.0f, 0.0f));

	physicsBody->setDynamic(false);
	physicsBody->setVelocity(Vect(0, -200));
	physicsBody->applyForce(Vect(0, -200));
	physicsBody->applyImpulse(Vect(0, -100));

	Humans->addComponent(physicsBody);
	eDir = eStopHuman;*/
	
	fSpeed = 0.001f;

}

void GameHumans::MoveChar(EHumanSprite DirX)
{
	eDir = DirX;
	//humans->stopAllActions();

	Vector<SpriteFrame*> MoveAnimFrames;
	MoveAnimFrames.reserve(3);
	if (eDir > 0)
	{
		if (fMale == 1)
		{
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Man_Right_1.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Man_Right_2.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Man_Right_3.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Man_Right_4.png", Rect(0, 0, 50, 48)));
		}
		else
		{
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Female_Right_1.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Female_Right_2.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Female_Right_3.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Female_Right_4.png", Rect(0, 0, 50, 48)));
		}
	}
	else if (eDir < 0)
	{
		if (fMale == 1)
		{
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Man_Left_1.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Man_Left_2.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Man_Left_3.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Man_Left_4.png", Rect(0, 0, 50, 48)));
		}
		else
		{
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Female_Left_1.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Female_Left_2.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Female_Left_3.png", Rect(0, 0, 50, 48)));
			MoveAnimFrames.pushBack(SpriteFrame::create("Humans/Female_Left_4.png", Rect(0, 0, 50, 48)));
		}
	}
	else
	{
		stop();
	}


	Animation* MoveAnimation = Animation::createWithSpriteFrames(MoveAnimFrames, 0.5f);
	Animate* animateMove = Animate::create(MoveAnimation);

	humans->runAction(RepeatForever::create(animateMove));
}

void GameHumans::stop(void)
{
	eDir = eStopHuman;
	humans->stopAllActions();

	if (fMale == 1)
	{
		Sprite::create("Humans/Man_Right_1.png", Rect(0, 0, 50, 48));
	}
	else
	{
		Sprite::create("Humans/Female_Right_1.png", Rect(0, 0, 50, 48));
	}

	/*Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("anim/Blue_Front2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("anim/Blue_Front1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("anim/Blue_Front3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("anim/Blue_Front1.png", Rect(0, 0, 65, 81)));

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animateIdle = Animate::create(animation);

	humans->runAction(RepeatForever::create(animateIdle));*/
}

void GameHumans::Update(float dt)
{
	if (eDir != EHumanSprite::eStopHuman)
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(1.0f, 0.f)*eDir);
		humans->runAction(moveEvent);
	}

	
	if(humans->getActionByTag(1)->isDone())
	{
		a = !a;
	}

	if (a == true)
	{
		MoveChar(EHumanSprite::eLeftHuman);
	}
	else
	{
		MoveChar(EHumanSprite::eRightHuman);
	}
}

void GameHumans::RotateChar(EHumanSprite dir)
{
	eDir = dir;
}

void GameHumans::HumanMove(float posX, float posY)
{
	humans->stopAllActions();
	//float diffX = posX - Bullets->getPosition().x;
	//float diffY = posY - Bullets->getPosition().y;
	float diffX = posX;
	float diffY = posY;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec * 2);
	humans->runAction(moveEvent);
}
