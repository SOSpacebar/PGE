#include "UpgradeMenu.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "Constants.h"
#include "AudioManager.h"
#include "ui/UIButton.h"

USING_NS_CC;

Scene* UpgradeMenu::createScene()
{
	auto scene = UpgradeMenu::create();

	//scene->getPhysicsWorld()->setGravity(Vec2(0, -98));

	////
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

	//auto layer = HelloWorld::create();
	//scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Upgrade.cpp\n");
}

// on "init" you need to initialize your instance
bool UpgradeMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

	//GRAVITY
	this->getPhysicsWorld()->setGravity(Vec2(0, -98));

	//
	this->getPhysicsWorld()->setDebugDrawMask(0xffff);



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

	// Node container for moveable sprites
	//moveableItems = Node::create();
	//moveableItems->setName("moveableItems");

	//moveableItems2 = Node::create();
	//moveableItems2->setName("moveableItems2");

	// Create a sprite object to load the image
	//auto sprite = Sprite::create("ground.png");
	auto background = Sprite::create("UpgradeMenu.png");




	// Load Main Sprite
//	males.Init("Humans/Man_Right_1.png", "maleSprite", (visibleSize.width * 0.5f)+150, visibleSize.height * 0.5f, 0, 9,1);
	//females.Init("Humans/Female_Right_1.png", "femaleSprite", (visibleSize.width * 0.5f) - 150, visibleSize.height * 0.5f, 0, 9,2);
	//nodeItems->addChild(males.getSprite(), 1);
	//nodeItems->addChild(females.getSprite(), 1);
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
	background->setAnchorPoint(Vec2::ZERO);
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

	float bS = 1.6f;
	int bX = (visibleSize.width - playingSize.width) - (background->getContentSize().width/360.0f);
	int bY = (visibleSize.height - playingSize.height)- (background->getContentSize().height*0.2f);

	auto newBackgroundNode = Sprite::createWithSpriteFrame(background->getSpriteFrame());
	newBackgroundNode->setAnchorPoint(Vec2::ZERO);
	newBackgroundNode->setPosition(bX, bY);
	newBackgroundNode->setScale(bS);
	bX += newBackgroundNode->getContentSize().width;
	nodeItems->addChild(newBackgroundNode, -1);

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

	//PLAY MUSIC
	AudioManager::GetInstance()->MusicPlay("BGM_Main", true);

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
	keyboardListener->onKeyPressed = CC_CALLBACK_2(UpgradeMenu::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(UpgradeMenu::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// Mouse Event
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(UpgradeMenu::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(UpgradeMenu::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(UpgradeMenu::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(UpgradeMenu::onMouseScroll, this);
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
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create(
    //                                       "CloseNormal.png",
    //                                       "CloseSelected.png",
    //                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    //if (closeItem == nullptr ||
    //    closeItem->getContentSize().width <= 0 ||
    //    closeItem->getContentSize().height <= 0)
    //{
    //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    //}
    //else
    //{
    //    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
    //    float y = origin.y + closeItem->getContentSize().height/2;
    //    closeItem->setPosition(Vec2(x,y));
    //}

    //// create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
	auto label = Label::createWithTTF("Upgrade", "fonts/Marker Felt.ttf", 45);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));
		label->setColor(Color3B(0, 0, 0));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	auto upgradeBuilding_0 = Button::create("BuildingUpgrade.png", "BuildingUpgradeComplete.png", "BuildingUpgradeComplete.png");
	upgradeBuilding_0->setScale(2,2);
	upgradeBuilding_0->setPosition(Vec2(origin.x + 200, origin.y + 800));
	upgradeBuilding_0->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeBuilding_0, 2);

	auto upgradeBuilding_1 = Button::create("BuildingUpgrade2Locked.png", "BuildingUpgrade2.png", "BuildingUpgrade2Complete.png");
	upgradeBuilding_1->setScale(2, 2);
	upgradeBuilding_1->setPosition(Vec2(origin.x + 400, origin.y + 850));
	upgradeBuilding_1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeBuilding_1, 2);

	auto upgradeBuilding_2 = Button::create("BuildingUpgrade2Locked.png", "BuildingUpgrade2.png", "BuildingUpgrade2Complete.png");
	upgradeBuilding_2->setScale(2, 2);
	upgradeBuilding_2->setPosition(Vec2(origin.x + 400, origin.y + 725));
	upgradeBuilding_2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeBuilding_2, 2);

	/*************************************************

	BULLET UPGRADE SECTIONS
	
	*************************************************/
	auto upgradeWeapon_0 = Button::create("BulletUpgrade.png", "BulletUpgradeComplete.png", "BulletUpgradeLocked.png");
	upgradeWeapon_0->setScale(2, 2);
	upgradeWeapon_0->setPosition(Vec2(origin.x + 200, origin.y + 500));
	upgradeWeapon_0->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeWeapon_0, 2);
	
	auto upgradeWeapon_1 = Button::create("BulletUpgrade2Locked.png", "BulletUpgrade2.png", "BulletUpgrade2Complete.png");
	upgradeWeapon_1->setScale(2, 2);
	upgradeWeapon_1->setPosition(Vec2(origin.x + 400, origin.y + 500));
	upgradeWeapon_1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeWeapon_1, 2);

	auto upgradeWeapon_2 = Button::create("BulletUpgrade3Locked.png", "BulletUpgrade3.png", "BulletUpgrade3Complete.png");
	upgradeWeapon_2->setScale(2, 2);
	upgradeWeapon_2->setPosition(Vec2(origin.x + 600, origin.y + 425));
	upgradeWeapon_2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeWeapon_2, 2);

	auto upgradeWeapon_3 = Button::create("BulletUpgrade4Locked.png", "BulletUpgrade4.png", "BulletUpgrade4sComplete.png");
	upgradeWeapon_3->setScale(2, 2);
	upgradeWeapon_3->setPosition(Vec2(origin.x + 600, origin.y + 550));
	upgradeWeapon_3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeWeapon_3, 2);
	/*************************************************

	HEALTH UPGRADE SECTIONS

	*************************************************/
	auto upgradeHealth_0 = Button::create("HealthIncrease.png", "HealthIncreaseComplete.png", "HealthIncreaseLocked.png");
	upgradeHealth_0->setScale(2, 2);
	upgradeHealth_0->setPosition(Vec2(origin.x + 200, origin.y + 200));
	upgradeHealth_0->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeHealth_0, 2);

	auto upgradeHealth_1 = Button::create("HealthIncrease2Locked.png", "HealthIncrease2.png","HealthIncrease2Complete.png");
	upgradeHealth_1->setScale(2, 2);
	upgradeHealth_1->setPosition(Vec2(origin.x + 400, origin.y + 200));
	upgradeHealth_1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeHealth_1, 2);

	auto upgradeHealth_2 = Button::create("HealthIncrease2Locked.png", "HealthIncrease2.png", "HealthIncrease2Complete.png");
	upgradeHealth_2->setScale(2 , 2);
	upgradeHealth_2->setPosition(Vec2(origin.x + 600, origin.y + 250));
	upgradeHealth_2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeHealth_2, 2);

	auto upgradeHealth_3 = Button::create("HealthIncrease2Locked.png", "HealthIncrease2.png", "HealthIncrease2Complete.png");
	upgradeHealth_3->setScale(2, 2);
	upgradeHealth_3->setPosition(Vec2(origin.x + 600, origin.y + 125));
	upgradeHealth_3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeHealth_3, 2);

    return true;
}


void UpgradeMenu::menuCloseCallback(Ref* pSender)
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

void UpgradeMenu::update(float delta)
{
	//mainCharacter.Update(delta);

	//for (auto bullet : m_Bullets) {
	//	// bullet->BulletMove();
	//}

	////Asteroid.Update(delta);

	//for (auto asteroid : Asteroid) {
	//	// bullet->BulletMove();
	//}

	//
	//SpawnTimer += delta;
	//
	//if (SpawnTimer > 1.f)
	//{
	//	asteroidsCount += 1;
	//	SpawnTimer = 0;
	//}

	//if (Asteroid.size() < asteroidsCount)
	//{
	//	GameAsteroid* Asteroids = new GameAsteroid();
	//	float AsteroidRandX = random(0, (int)(visibleSize.width - 10));
	//	Asteroids->Init("Asteroid.png", "Asteroids", AsteroidRandX, (visibleSize.height - 10), 0);

	//	Asteroid.push_back(Asteroids);

	//	// Add Bullets to Movable
	//	moveableItems->addChild(Asteroids->getSprite(), 1);
	//}
}

void UpgradeMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	/*case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		mainCharacter.MoveChar(EAction::eRight);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		mainCharacter.MoveChar(EAction::eLeft);
		break;*/
	case EventKeyboard::KeyCode::KEY_SPACE:
		SceneManager::GetInstance()->RunSceneWithType(SceneType::LOADING, TransitionType::CROSSFADE);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		SceneManager::GetInstance()->RunSceneWithType(SceneType::WINSCENE, TransitionType::CROSSFADE);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		SceneManager::GetInstance()->RunSceneWithType(SceneType::LOSESCENE, TransitionType::CROSSFADE);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		SceneManager::GetInstance()->RunSceneWithType(SceneType::UPGRADESCENE, TransitionType::CROSSFADE);
		break;
	case EventKeyboard::KeyCode::KEY_W:
		SceneManager::GetInstance()->RunSceneWithType(SceneType::SETTING, TransitionType::CROSSFADE);
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		SceneManager::GetInstance()->RunSceneWithType(SceneType::MAINMENU, TransitionType::CROSSFADE);
		break;
	default:
		break;
	}

	log("Key with keycode %d pressed", keyCode);
}

void UpgradeMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//mainCharacter.MoveChar(EAction::eStop);
	log("Key with keycode %d released", keyCode);
}

void UpgradeMenu::onMouseMove(Event * mouse)
{
	EventMouse* eventMouse = static_cast<EventMouse*>(mouse);
	EventMouse *e = (EventMouse*)mouse;

	//mainCharacter.SetCharAim(eventMouse->getLocationInView());
	/*if (!b_mouseclicked)
		Bullet.SetShoot(eventMouse->getLocationInView());*/
}

void UpgradeMenu::onMouseUp(Event * mouse)
{
	EventMouse* eventMouse = static_cast<EventMouse*>(mouse);
	EventMouse *e = (EventMouse*)mouse;

	//Vec2 dir = Vec2(e->getCursorX(), e->getCursorY()) - Vec2(visibleSize.width * 0.5f, (visibleSize.height - playingSize.height));

	//GameBullet* proBullet = new GameBullet();
	//proBullet->Init("Bullet.png", "Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);

	//proBullet->SetShoot(e->getLocationInView());
	//proBullet->BulletMove();

	//m_Bullets.push_back(proBullet);

	//// Add Bullets to Movable
	//moveableItems->addChild(proBullet->getSprite(), 1);
	b_mouseclicked = true;
}

void UpgradeMenu::onMouseDown(Event * mouse)
{
	
}

void UpgradeMenu::onMouseScroll(Event * mouse)
{
}

void UpgradeMenu::onButtonClick()
{
}

