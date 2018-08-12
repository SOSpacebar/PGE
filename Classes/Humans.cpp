#include "Humans.h"
#include "Constants.h"

void GameHumans::Init(const char * pngName, const char * name, float posX, float posY, float rotation, float scale,bool fM)
{
	// Load Main Sprite
	this->setTexture(pngName);
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(posX, posY);
	this->setRotation(rotation);
	this->setName(name);
	this->setScale(scale);
	eDir = eStopHuman;

	stop();
	//Vector<SpriteFrame*> animFrames;
	
	//Constant::GetInstance()->GetVisableSize().width = playingSize;
	fMale = fM;

	//auto moveEvent = MoveBy::create(5, Vec2(Constant::GetInstance()->GetVisableSize().width, 0));
	//moveEvent->setTag(1);
	//this->runAction(moveEvent);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), nullptr);
	//this->runAction(RepeatForever::create(sequence));

	/*auto physicsBody = PhysicsBody::createBox(Size(Humans->getContentSize().width, Humans->getContentSize().height),
		PhysicsMaterial(1.0f, 0.0f, 0.0f));

	physicsBody->setDynamic(false);
	physicsBody->setVelocity(Vect(0, -200));
	physicsBody->applyForce(Vect(0, -200));
	physicsBody->applyImpulse(Vect(0, -100));

	Humans->addComponent(physicsBody);
	eDir = eStopHuman;*/
	
	fSpeed = 0.001f;

	this->scheduleUpdate();
}

void GameHumans::MoveChar(EHumanSprite DirX)
{
	eDir = DirX;
	this->stopAllActions();

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

	this->runAction(RepeatForever::create(animateMove));
}

void GameHumans::stop(void)
{
	eDir = eStopHuman;
	this->stopAllActions();

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

	this->runAction(RepeatForever::create(animateIdle));*/
}

void GameHumans::update(float dt)
{
	auto moveEvent = MoveBy::create(0.0f, Vec2(10.0f, 0.f)*eDir);
	this->runAction(moveEvent);

	if (eDir == EHumanSprite::eStopHuman)
	{
		if (fMale)
			MoveChar(EHumanSprite::eRightHuman);
		else
			MoveChar(EHumanSprite::eLeftHuman);
		
	}
		

	
	if(this->getPosition().x > Constant::GetInstance()->GetVisableSize().width/* && this->getPosition().x > Constant::GetInstance()->GetVisableSize().width - 100*/)
	{
		if (eDir != EHumanSprite::eLeftHuman)
			MoveChar(EHumanSprite::eLeftHuman);
	}
	if (this->getPosition().x < 0 /*&& this->getPosition().x < 10*/)
	{
		if (eDir != EHumanSprite::eRightHuman)
			MoveChar(EHumanSprite::eRightHuman);
	}
}

//void GameHumans::RotateChar(EHumanSprite dir)
//{
//	eDir = dir;
//}

void GameHumans::HumanMove(float posX, float posY)
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
