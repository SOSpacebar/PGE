#include "Character.h"
#include "HelloWorldScene.h"

void GameChar::Init(const char * pngName, const char * name, float posX, float posY)
{
	// Load Main Sprite
	mainSprite = Sprite::create(pngName);
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(posX, posY);
	mainSprite->setName(name);
	eDir = eStop;
	fSpeed = 0.01f;

	//StopChar();

	//Run animation though sprite sheet
	//SpriteBatchNode* spritebatch = SpriteBatchNode::create("sprite.png");
	//SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	//cache->addSpriteFramesWithFile("sprite.plist");

	//spritebatch->addChild(Sprite::createWithSpriteFrameName("Blue_Back1.png"));
	//mainSprite->addChild(spritebatch);

	//Vector<SpriteFrame*> animFrames(3);
	//char str[100] = {0};

	//for (int i = 0; i < 3; ++i)
	//{
	//	sprintf(str, "Blue_Back%d.png", i);
	//	SpriteFrame* frame = cache->getSpriteFrameByName(str);
	//	animFrames.pushBack(frame);
	//}

	//auto animCache = AnimationCache::getInstance();
	//animCache->addAnimationsWithFile("sprite_ani.plist");

	//auto animation = animCache->animationByName("walk_right");

	//auto animate = Animate::create(animation);
	//mainSprite->runAction(animate);

}

void GameChar::MoveChar(EAction dir)
{
	eDir = dir;
	mainSprite->stopAllActions();


	// Load Animation State Sprite
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(3);

	if (dir > 0)
	{
		animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 56, 75)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 56, 75)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 56, 75)));
	}
	else if (dir < 0)
	{
		animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 56, 75)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 56, 75)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 56, 75)));
	}
	else
	{
		StopChar();
	}

	//Load the animation for movement state
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animate = Animate::create(animation);

	//run it and repeat it forever
	mainSprite->runAction(RepeatForever::create(animate));
}

void GameChar::StopChar()
{
	mainSprite->stopAllActions();

	// Load Idle State Sprite
	Vector<SpriteFrame*> idleAnimFrames;
	idleAnimFrames.reserve(4);
	idleAnimFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 60, 75)));
	idleAnimFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 60, 75)));
	idleAnimFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 60, 75)));
	idleAnimFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 60, 75)));

	//Load the animation for Idle state
	Animation* idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.5f);
	Animate* animateIdle = Animate::create(idleAnimation);

	//run it and repeat it forever
	mainSprite->runAction(RepeatForever::create(animateIdle));
}

void GameChar::MoveCharByCoord(float posX, float posY)
{
	mainSprite->stopAllActions();
	float diffX = posX - mainSprite->getPosition().x;
	float diffY = posY - mainSprite->getPosition().y;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec);
	
	auto callbackStop = CallFunc::create([]() {
		auto scene = Director::getInstance()->getRunningScene();
		HelloWorld* HWScene = dynamic_cast<HelloWorld*>(scene);
		if (HWScene != NULL)
		{
			HWScene->getChar()->StopChar();
		}
	});
	
	auto seq = Sequence::create(moveEvent, callbackStop, nullptr);
	mainSprite->runAction(seq);

	// Load Back State Sprite
	Vector<SpriteFrame*> backAnimFrames;
	backAnimFrames.reserve(4);
	backAnimFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 60, 75)));
	backAnimFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 60, 75)));
	backAnimFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 60, 75)));
	backAnimFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 60, 75)));

	//Load the animation for Idle state
	Animation* animation = Animation::createWithSpriteFrames(backAnimFrames, 0.5f);
	Animate* animate = Animate::create(animation);

	//run it and repeat it forever
	mainSprite->runAction(RepeatForever::create(animate));
}

void GameChar::Update(float)
{
	if (eDir != EAction::eStop)
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(eDir, 0.f));
		mainSprite->runAction(moveEvent);
	}
}
