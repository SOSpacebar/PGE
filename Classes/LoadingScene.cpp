#include "LoadingScene.h"
#include "SceneManager.h"
#include "Constants.h"


USING_NS_CC;

Scene* LoadingScene::createScene()
{
	auto scene = LoadingScene::create();

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::initWithPhysics())
	{
		return false;
	}


	this->scheduleUpdate();

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Playing Size
	playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	// Node container for non-moveable sprites
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	auto groundItems = Node::create();
	groundItems->setName("groundItems");

	auto label = Label::createWithTTF("Loading Next Scene", "fonts/Marker Felt.tff", 24);
	auto textLabel = Label::createWithTTF("0%", "fonts/Marker Felt.tff", 24);

	if (label != nullptr)
	{
		label->setPosition(Vec2((int)visibleSize.width >> 1, (int)visibleSize.height >> 1));
		this->addChild(label, 1);
	}

	if (textLabel != nullptr)
	{
		textLabel->setPosition(Vec2((int)visibleSize.width >> 1, ((int)visibleSize.height >> 1) - 30));
		this->addChild(textLabel, 1);
	}

	/*resources[0] = "lol";
	resources[1] = "lol";
	resources[2] = "lol";
	resources[3] = "lol";
	resources[4] = "lol";
	resources[5] = "lol";
	resources[6] = "lol";
	resources[7] = "lol";
	resources[8] = "lol";

	auto director = Director::getInstance();
	TextureCache* textureCache = director->getTextureCache();
	textureCache->addImageAsync(resources[0], CC_CALLBACK_1(LoadingScene::LoadingTextureFinished, this));*/

	// create the sprite used as a stencil
	auto dropletSprite = Sprite::create();
	dropletSprite->setTexture("White_Front1.png");

	// create the clipping node
	auto clipper = ClippingNode::create();
	clipper->setPosition((Vec2((int)visibleSize.width >> 1, (int)visibleSize.height >> 1)));

	// attach the stencil to the clipping node and add it as a child,
	// so the iamge itself can act as the background layer
	clipper->setStencil(dropletSprite);
	clipper->addChild(dropletSprite);

	// create the sprite used for the gauge
	// image needs the same width as the stencil
	auto gaugeSprite = Sprite::create();
	gaugeSprite->setTexture("Blue_Front1.png");

	// create a progress timer, working on the gauge sprite
	progressTimer = ProgressTimer::create(gaugeSprite);

	// set the midpoint to the center bottom, as the gauge is filling up from the bottom
	// to the top
	progressTimer->setMidpoint(Vec2(0.5f, 0.0f));

	// the gauge is working linear
	progressTimer->setType(ProgressTimer::Type::BAR);

	// the progress timer is only working on the y axis of the gauge
	// the x axis stays at 100 % all the time
	progressTimer->setBarChangeRate(Vec2(0.0f, 1.0f));

	//Set Percent value
	percent = 0;

	// set the filling of the gauge in percent; from 0-100%
	progressTimer->setPercentage(percent);

	// add the progress timer as a child to the clipper, so the gauge will follow the
	// image form
	clipper->addChild(progressTimer);

	// add the clipping node to the layer
	addChild(clipper, 1000, "loadingimage");

	// Node container for moveable sprites
	//moveableItems = Node::create();
	//moveableItems->setName("moveableItems");

	//moveableItems2 = Node::create();
	//moveableItems2->setName("moveableItems2");

	// Create a sprite object to load the image
	//auto sprite = Sprite::create("ground.png");
	//auto background = Sprite::create("LoadingScene.png");


	// Load Main Sprite
	//mainCharacter.Init("MainCannon.png", "mainSprite", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), 0);
	//// Loading Bullet Sprites
	//Bullet.Init("Bullet.png", "Bullets", 100, (visibleSize.height - playingSize.height), 0);
	// Loading Asteroid Sprites
	//Asteroid.Init("Asteroid.png", "Asteroids", 500, (visibleSize.height - 10), 0);

	//auto mainSprite = Sprite::create("Blue_Front1.png");
	//mainSprite->setAnchorPoint(Vec2(0, 0));
	//mainSprite->setPosition(100, (visibleSize.height - playingSize.height));
	//mainSprite->setName("mainSprite");

	// Set anchor point and position of object
	//sprite->setAnchorPoint(Vec2::ZERO);
	//background->setAnchorPoint(Vec2::ZERO);
	//sprite->setPosition(0, 0);

	// Add object into the node container
	/*float tempNum = 1.1f;
	int loopSize = std::ceil(visibleSize.width / sprite->getContentSize().width);
	int sX = 0;
	int sY = (visibleSize.height - playingSize.height) - sprite->getContentSize().height/ tempNum;

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

	groundItems->addChild(newNode, 1);
	}*/

	//float bS = 1.9f;
	//int bX = (visibleSize.width - playingSize.width) - (background->getContentSize().width / 5.2f);
	//int bY = (visibleSize.height - playingSize.height) - (background->getContentSize().height*0.2f);

	/*auto newBackgroundNode = Sprite::createWithSpriteFrame(background->getSpriteFrame());
	newBackgroundNode->setAnchorPoint(Vec2::ZERO);
	newBackgroundNode->setPosition(bX, bY);
	newBackgroundNode->setScale(bS);
	bX += newBackgroundNode->getContentSize().width;
	nodeItems->addChild(newBackgroundNode, -1);*/

	// Add mainSprite to moveable
	//moveableItems2->addChild(mainCharacter.getSprite(), 1);
	// Add Bullets to Movable
	/*moveableItems->addChild(Bullet.getSprite(), 1);*/
	// Add Asteroids to Movable
	//moveableItems->addChild(Asteroid.getSprite(), 1);

	// Add the note container into the scene graph
	this->addChild(nodeItems, 1);
	//this->addChild(moveableItems, 2);
	//this->addChild(groundItems, 2);
	//this->addChild(moveableItems2, 3);

	// Movement 
	//auto moveEvent = MoveBy::create(5, Vec2(200, 0));
	//mainSprite->runAction(moveEvent);

	// Sequence
	//auto delay = DelayTime::create(5.0f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	//mainSprite->runAction(sequence);

	// Keyboard Event
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(LoadingScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(LoadingScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// Mouse Event
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(LoadingScene::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(LoadingScene::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(LoadingScene::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(LoadingScene::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// Touch Event
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	touchListener->onTouchMoved = [](Touch* touch, Event* event) {
		return true;
	};
	touchListener->onTouchEnded = [](Touch* touch, Event* event) {
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}


void LoadingScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

void LoadingScene::LoadingTextureFinished(Texture2D * texture)
{
	auto director = Director::getInstance();
}

void LoadingScene::update(float delta)
{
	progressTimer->setPercentage(percent);

	if (percent < 100.f)
	{
		percent += delta * 15;
	}
	else if (percent > 100.f)
	{
		SceneManager::GetInstance()->RunSceneWithType(SceneType::GAMEPLAY, TransitionType::FADE);
	}
}

void LoadingScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		//SceneManager::GetInstance()->RunSceneWithType(SceneType::GAMEPLAY, TransitionType::FADE);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		break;
	default:
		break;
	}

	log("Key with keycode %d pressed", keyCode);
}

void LoadingScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//mainCharacter.MoveChar(EAction::eStop);
	log("Key with keycode %d released", keyCode);
}

void LoadingScene::onMouseMove(Event * mouse)
{
	EventMouse* eventMouse = static_cast<EventMouse*>(mouse);
	EventMouse *e = (EventMouse*)mouse;
}

void LoadingScene::onMouseUp(Event * mouse)
{
	EventMouse* eventMouse = static_cast<EventMouse*>(mouse);
	EventMouse *e = (EventMouse*)mouse;

	b_mouseclicked = true;
}

void LoadingScene::onMouseDown(Event * mouse)
{

}

void LoadingScene::onMouseScroll(Event * mouse)
{
}

