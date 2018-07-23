#include "HelloWorldScene.h"
#include "Constants.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = HelloWorld::create();

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
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
	moveableItems = Node::create();
	moveableItems->setName("moveableItems");

	moveableItems2 = Node::create();
	moveableItems2->setName("moveableItems2");

	// Create a sprite object to load the image
	auto sprite = Sprite::create("ground.png");
	auto background = Sprite::create("background.png");


	// Load Main Sprite
	mainCharacter.Init("MainCannon.png", "mainSprite", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), 0);
	males.Init("Humans/Man_Right_1.png", "maleSprite", (visibleSize.width * 0.5f) + 150, visibleSize.height * 0.2f, 0, 2, 0);
	females.Init("Humans/Female_Right_1.png", "femaleSprite", (visibleSize.width * 0.5f) - 150, visibleSize.height * 0.2f, 0, 2, 1);

	nodeItems->addChild(males.getSprite(), 1);
	nodeItems->addChild(females.getSprite(), 1);

	// Spawn Manager
	spawner.Init(moveableItems);
	spawner.AddWave(10, 0.5f);
	//GameAsteroid* asteroids = new GameAsteroid();
	//float asteroidRandX = random(0, (int)(visibleSize.width - 10));
	//asteroids->Init("Asteroid.png", "Asteroids", asteroidRandX, (visibleSize.height - 10), 0, &mainCharacter);
	//moveableItems->addChild(asteroids, 1);

	//// Loading Bullet Sprites
	//Bullet.Init("Bullet.png", "Bullets", 100, (visibleSize.height - playingSize.height), 0);
	// Loading Asteroid Sprites
	//Asteroid.Init("Asteroid.png", "Asteroids", 500, (visibleSize.height - 10), 0);

	//auto mainSprite = Sprite::create("Blue_Front1.png");
	//mainSprite->setAnchorPoint(Vec2(0, 0));
	//mainSprite->setPosition(100, (visibleSize.height - playingSize.height));
	//mainSprite->setName("mainSprite");

	// Set anchor point and position of object
	sprite->setAnchorPoint(Vec2::ZERO);
	background->setAnchorPoint(Vec2::ZERO);
	//sprite->setPosition(0, 0);

	// Add object into the node container
	float tempNum = 1.1f;
	int loopSize = std::ceil(visibleSize.width / sprite->getContentSize().width);
	int sX = 0;
	int sY = (visibleSize.height - playingSize.height) - sprite->getContentSize().height;

	for (size_t i = 0; i < loopSize; ++i)
	{
		auto newNode = Sprite::createWithSpriteFrame(sprite->getSpriteFrame());
		newNode->setAnchorPoint(Vec2::ZERO);
		newNode->setPosition(sX, sY);
		newNode->setScaleY(1.2f);
		sX += newNode->getContentSize().width;
		
		auto physicsBody = PhysicsBody::createBox(Size(newNode->getContentSize().width, newNode->getContentSize().height),
			PhysicsMaterial(1.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		newNode->addComponent(physicsBody);

		groundItems->addChild(newNode, 1);
	}

	float bS = 1.7f;
	int bX = (visibleSize.width - playingSize.width);// - background->getContentSize().width;
	int bY = (visibleSize.height - playingSize.height)-(sprite->getContentSize().height*1.8); //- background->getContentSize().height;

	auto newBackgroundNode = Sprite::createWithSpriteFrame(background->getSpriteFrame());
	newBackgroundNode->setAnchorPoint(Vec2::ZERO);
	newBackgroundNode->setPosition(bX, bY);
	newBackgroundNode->setScale(bS);
	bX += newBackgroundNode->getContentSize().width;
	nodeItems->addChild(newBackgroundNode, -1);

	// Add mainSprite to moveable
	moveableItems2->addChild(mainCharacter.getSprite(), 1);
	// Add Bullets to Movable
	/*moveableItems->addChild(Bullet.getSprite(), 1);*/
	// Add Asteroids to Movable
	//moveableItems->addChild(Asteroid.getSprite(), 1);

	//auto moveEvent = MoveBy::create(5, Vec2(500, 0));
	//males->runAction(moveEvent);

	//auto delay = DelayTime::create(5.0f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	//humans->runAction(sequence);

	// Add the note container into the scene graph
	this->addChild(nodeItems, 1);
	this->addChild(moveableItems, 2);
	this->addChild(groundItems, 2);
	this->addChild(moveableItems2, 3);

	//Health Bar
	// create the sprite used as a stencil
	auto baseSprite = Sprite::create();
	baseSprite->setTexture("dull_bar.png");

	// create the clipping node
	auto clipper = ClippingNode::create();
	clipper->setPosition((Vec2((int)visibleSize.width >> 1, visibleSize.height - playingSize.height - 40.f)));

	// attach the stencil to the clipping node and add it as a child,
	// so the iamge itself can act as the background layer
	clipper->setStencil(baseSprite);
	clipper->addChild(baseSprite);

	// create the sprite used for the gauge
	// image needs the same width as the stencil
	auto gaugeSprite = Sprite::create();
	gaugeSprite->setTexture("red_bar.png");

	// create a progress timer, working on the gauge sprite
	progressTimer = ProgressTimer::create(gaugeSprite);

	// set the midpoint to the center bottom, as the gauge is filling up from the bottom
	// to the top
	progressTimer->setMidpoint(Point(0, 0));

	// the gauge is working linear
	progressTimer->setType(ProgressTimer::Type::BAR);

	// the progress timer is only working on the y axis of the gauge
	// the x axis stays at 100 % all the time
	progressTimer->setBarChangeRate(Vec2(1.0f, 0.0f));

	//Set Percent value
	gameStats.SetPlayerHealth(100);

	// set the filling of the gauge in percent; from 0-100%
	progressTimer->setPercentage(gameStats.GetPlayerHealth());

	// add the progress timer as a child to the clipper, so the gauge will follow the
	// image form
	clipper->addChild(progressTimer);

	// add the clipping node to the layer
	addChild(clipper, 1000, "loadingimage");

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
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// Mouse Event
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
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


	// Collision CallBack
	auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::OnContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Set into Constants
	Constant::GetInstance()->SetVisableSize(visibleSize);
	Constant::GetInstance()->SetHealth(gameStats.GetPlayerHealth());
	Constant::GetInstance()->SetGameObjectCount(0);

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

	scoreNum = 0;

    label = Label::createWithTTF("Score: "+ std::to_string(scoreNum), "fonts/Marker Felt.ttf", 45);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));
		label->setColor(Color3B(0, 0, 0));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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

bool HelloWorld::OnContactBegin(cocos2d::PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody();
	auto nodeB = contact.getShapeB()->getBody();

	if (nodeA && nodeB)
	{
		if (nodeA->getCollisionBitmask() == static_cast<int>(CollisionType::ASTEROID) && nodeB->getCollisionBitmask() == static_cast<int>(CollisionType::ROCKET))
		{
			nodeA->getNode()->removeFromParentAndCleanup(true);
			nodeB->getNode()->removeFromParentAndCleanup(true);
			scoreNum += 10;
			label->setString("Score: " + std::to_string(scoreNum));

			Constant::GetInstance()->SetGameObjectCount(Constant::GetInstance()->GetGameObjectCount() - 1);
			log("Delete GameObject Count %d", Constant::GetInstance()->GetGameObjectCount());
		}
	}

	//bodies can collide
	return true;
}


void HelloWorld::update(float delta)
{
	mainCharacter.Update(delta);
	spawner.Update(delta);

	//for (auto bullet : m_Bullets) {
	//	if (bullet->getSprite()->getPosition().y > visibleSize.height)
	//	{
	//		bullet->getSprite()->removeFromParentAndCleanup(true);
	//	}
	//}

	//Asteroid.Update(delta);

	//for (auto asteroid : asteroid) {
	//	//if (asteroid->getSprite()->getPosition().y < playingSize.height)
	//	//{
	//	//	asteroid->getSprite()->removeFromParentAndCleanup(true);
	//	//	health -= 5;
	//	//}
	//}

	
	//spawnTimer += delta;
	//
	//if (spawnTimer > 1.f)
	//{
	//	GameAsteroid* asteroids = new GameAsteroid();
	//	float asteroidRandX = random(0, (int)(visibleSize.width - 10));
	//	asteroids->Init("Asteroid.png", "Asteroids", asteroidRandX, (visibleSize.height - 10), 0, &mainCharacter);

	//	// Add Bullets to Movable
	//	moveableItems->addChild(asteroids, 1);
	//	spawnTimer = 0;
	//}

	progressTimer->setPercentage(Constant::GetInstance()->GetHealth());

	//if (health > 0)
	//{
	//	health -= delta * 15;
	//}
	//else if (percent > 100.f)
	//{
	//	SceneManager::GetInstance()->RunSceneWithType(SceneType::GAMEPLAY, TransitionType::FADE);
	//}

	//if (Asteroid.size() < asteroidsCount)
	//{
	//	

	//	Asteroid.push_back(Asteroids);

	//	
	//}
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	/*case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		mainCharacter.MoveChar(EAction::eRight);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		mainCharacter.MoveChar(EAction::eLeft);
		break;*/
	case EventKeyboard::KeyCode::KEY_A:
		mainCharacter.RotateCharByDir(EAction::eRight);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		mainCharacter.RotateCharByDir(EAction::eLeft);
		break;
	case EventKeyboard::KeyCode::KEY_1:
		firstBullet = true;
		secondBullet = false;
		thirdBullet = false;
		fourthBullet = false;
		break;
	case EventKeyboard::KeyCode::KEY_2:
		firstBullet = false;
		secondBullet = true;
		thirdBullet = false;
		fourthBullet = false;
		break;
	case EventKeyboard::KeyCode::KEY_3:
		firstBullet = false;
		secondBullet = false;
		thirdBullet = true;
		fourthBullet = false;
		break;
	case EventKeyboard::KeyCode::KEY_4:
		firstBullet = false;
		secondBullet = false;
		thirdBullet = false;
		fourthBullet = true;
		break;
	default:
		break;
	}

	log("Key with keycode %d pressed", keyCode);
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	mainCharacter.MoveChar(EAction::eStop);
	log("Key with keycode %d released", keyCode);
}

void HelloWorld::onMouseMove(Event * mouse)
{
	EventMouse* eventMouse = static_cast<EventMouse*>(mouse);
	EventMouse *e = (EventMouse*)mouse;

	mainCharacter.SetCharAim(eventMouse->getLocationInView());
	/*if (!b_mouseclicked)
		Bullet.SetShoot(eventMouse->getLocationInView());*/
}

void HelloWorld::onMouseUp(Event * mouse)
{
	EventMouse* eventMouse = static_cast<EventMouse*>(mouse);
	EventMouse *e = (EventMouse*)mouse;

	Vec2 dir = Vec2(e->getCursorX(), e->getCursorY()) - Vec2(visibleSize.width * 0.5f, (visibleSize.height - playingSize.height));

	GameBullet* proBullet = new GameBullet();
	GameBullet* bullet = new GameBullet();
	GameBullet* thiBullet = new GameBullet();

	if(firstBullet)
		proBullet->Init("Bullet.png", "Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
	else if (secondBullet)
	{
		proBullet->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f-20, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
		bullet->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f+20, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);

		bullet->SetShoot(e->getLocationInView());
		bullet->BulletMove();

		moveableItems->addChild(bullet, 1);
	}
	else if (thirdBullet)
	{
		proBullet->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 25, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
		bullet->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
		thiBullet->Init("Bullet.png", "3Bullets", visibleSize.width * 0.5f + 25, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);

		bullet->SetShoot(e->getLocationInView());
		bullet->BulletMove();
		thiBullet->SetShoot(e->getLocationInView());
		thiBullet->BulletMove();

		moveableItems->addChild(bullet, 1);
		moveableItems->addChild(thiBullet, 1);
	}
	else if (fourthBullet)
	{
		proBullet->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 25, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
		bullet->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
		thiBullet->Init("Bullet.png", "3Bullets", visibleSize.width * 0.5f + 25, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
		
		bullet->SetShoot(e->getLocationInView());
		bullet->BulletMove();
		thiBullet->SetShoot(e->getLocationInView());
		thiBullet->BulletMove();

		moveableItems->addChild(bullet, 1);
		moveableItems->addChild(thiBullet, 1);
	}

	proBullet->SetShoot(e->getLocationInView());
	proBullet->BulletMove();

	//m_Bullets.push_back(proBullet);

	// Add Bullets to Movable
	moveableItems->addChild(proBullet, 1);
	b_mouseclicked = true;
}

void HelloWorld::onMouseDown(Event * mouse)
{
	
}

void HelloWorld::onMouseScroll(Event * mouse)
{
}

