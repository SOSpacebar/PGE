#include "HelloWorldScene.h"
#include "SceneManager.h"
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
	//males.Init("Humans/Man_Right_1.png", "maleSprite", (visibleSize.width * 0.5f) + 150, visibleSize.height * 0.2f, 0, 2, 0);
	//females.Init("Humans/Female_Right_1.png", "femaleSprite", (visibleSize.width * 0.5f) - 150, visibleSize.height * 0.2f, 0, 2, 1);

	//nodeItems->addChild(males.getSprite(), 1);
	//nodeItems->addChild(females.getSprite(), 1);

	for (int i = 0; i < 4; ++i)
	{
		GameHumans *human = new GameHumans();
		if (i % 2 == 0) //Male
			human->Init("Humans/Man_Right_1.png", "maleSprite", random(0.f, visibleSize.width), visibleSize.height * 0.2f, 0, 2, 1);
		else
			human->Init("Humans/Female_Right_1.png", "femaleSprite", random(0.f, visibleSize.width), visibleSize.height * 0.2f, 0, 2, 0);

		moveableItems->addChild(human, 1);
	}

	// Spawn Manager
	spawner.Init(moveableItems);

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
	//keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// Mouse Event
	//auto mouseListener = EventListenerMouse::create();
	//mouseListener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	//mouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	//mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	//mouseListener->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

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
	int healthLvl = (int)Constant::GetInstance()->GetHealthLevel();
	Constant::GetInstance()->SetVisableSize(visibleSize);
	if (healthLvl != (int)GameStats::HEALTHLEVEL3_1)
		Constant::GetInstance()->SetMaxHealth(100 * healthLvl);
	else
	{
		Constant::GetInstance()->SetMaxHealth(100 * 2);
		Constant::GetInstance()->SetRegRate(0.1f);
	}
	Constant::GetInstance()->SetHealth(Constant::GetInstance()->GetMaxHealth());
	Constant::GetInstance()->SetGameObjectCount(0);
	Constant::GetInstance()->SetScore(Constant::GetInstance()->GetScore());
	
	// set the filling of the gauge in percent; from 0-100%
	progressTimer->setPercentage(Constant::GetInstance()->GetHealth());

	if (Constant::GetInstance()->GetHealth() <= 0)
	{
		SceneManager::GetInstance()->RunSceneWithType(SceneType::LOSESCENE, TransitionType::CROSSFADE);
	}
	// add the progress timer as a child to the clipper, so the gauge will follow the
	// image form
	clipper->addChild(progressTimer);

	// add the clipping node to the layer
	addChild(clipper, 1000, "loadingimage");



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
    label = Label::createWithTTF("Day: " + std::to_string(Constant::GetInstance()->GetLevel()) + "\nMoney: "+ std::to_string(Constant::GetInstance()->GetScore()), "fonts/Marker Felt.ttf", 35);
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

	auto LeftButton = Button::create("Left_Buttons.png", "Left_Buttons.png");
	LeftButton->setScale(1, 1);
	LeftButton->setPosition(Vec2(origin.x + visibleSize.width / 15, origin.y + visibleSize.height / 13 + origin.y));
	LeftButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			mainCharacter.RotateCharByDirLeft();
			break;
		case ui::Widget::TouchEventType::ENDED:
			mainCharacter.StopRotation();
			break;
		default:
			break;
		}
	});
	this->addChild(LeftButton, 2);

	
	auto RightButton = Button::create("Right_Buttons.png", "Right_Buttons.png");
	RightButton->setScale(1, 1);
	RightButton->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 13 + origin.y));
	RightButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			mainCharacter.RotateCharByDirRight();
			break;
		case ui::Widget::TouchEventType::ENDED:
			mainCharacter.StopRotation();
			break;
		default:
			break;
		}
	});
	this->addChild(RightButton, 2);

	auto ShootButton = Button::create("Fire_Buttons.png", "Fire_Buttons.png");
	ShootButton->setScale(1, 1);
	ShootButton->setPosition(Vec2(origin.x + visibleSize.width / 1.1, origin.y + visibleSize.height / 13 + origin.y));
	ShootButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			JustShoot();
			break;
		}
		default:
			break;
		}
	});
	this->addChild(ShootButton, 2);
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
			int score = Constant::GetInstance()->GetScore();
			Constant::GetInstance()->SetScore((score += 10));
			label->setString("Day: " + std::to_string(Constant::GetInstance()->GetLevel()) + "\nMoney: " + std::to_string(Constant::GetInstance()->GetScore()));

			Constant::GetInstance()->SetGameObjectCount(Constant::GetInstance()->GetGameObjectCount() - 2);
			log("Delete GameObject Count %d", Constant::GetInstance()->GetGameObjectCount());

			//EFFECTS ON Explosion 
			auto _emitter = ParticleExplosion::create();
			_emitter->retain();
			_emitter->setStartSizeVar(3.f);
			_emitter->setStartSize(5.f);
			_emitter->setPosition(nodeA->getPosition());
			_emitter->setLifeVar(0);
			_emitter->setLife(1);
			_emitter->setSpeed(100);
			_emitter->setSpeedVar(0);
			_emitter->setEmissionRate(10000);
			_emitter->setStartColor(Color4F::RED);
			_emitter->setEndColor(Color4F::ORANGE);
			addChild(_emitter, 10);

			_emitter->setAutoRemoveOnFinish(true);
		}
	}

	//bodies can collide
	return true;
}


void HelloWorld::update(float delta)
{
	mainCharacter.Update(delta);
	spawner.Update(delta);

	
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

	if (Constant::GetInstance()->GetRegRate() > 0)
	{
		if (Constant::GetInstance()->GetHealth() < Constant::GetInstance()->GetMaxHealth())
		{
			Constant::GetInstance()->SetHealth(Constant::GetInstance()->GetHealth() + Constant::GetInstance()->GetRegRate());
		}
	}

	progressTimer->setPercentage(Constant::GetInstance()->GetHealth());

	//if (health > 0)
	//{
	//	health -= delta * 15;
	//}
	//else if (percent > 100.f)
	//{
	//	SceneManager::GetInstance()->RunSceneWithType(SceneType::GAMEPLAY, TransitionType::FADE);
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
		mainCharacter.RotateCharByDirLeft();
		break;
	case EventKeyboard::KeyCode::KEY_D:
		mainCharacter.RotateCharByDirRight();
		break;
	case EventKeyboard::KeyCode::KEY_1:
		Constant::GetInstance()->SetAttackLevel(GameStats::SINGLEROUND);
		break;
	case EventKeyboard::KeyCode::KEY_2:
		Constant::GetInstance()->SetAttackLevel(GameStats::DOUBLEROUND);
		break;
	case EventKeyboard::KeyCode::KEY_3:
		Constant::GetInstance()->SetAttackLevel(GameStats::TRIPLEROUND);
		break;
	case EventKeyboard::KeyCode::KEY_4:
		Constant::GetInstance()->SetAttackLevel(GameStats::SPLITROUND);
		break;
	default:
		break;
	}

	log("Key with keycode %d pressed", keyCode);
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

	int bulletSize = (int)Constant::GetInstance()->GetAttackLevel() + 1;
	std::vector<GameBullet*> bulletBox;

	while (bulletBox.size() < bulletSize) {
		bulletBox.push_back(new GameBullet());
	}

	if(Constant::GetInstance()->GetAttackLevel() == GameStats::SINGLEROUND)
		bulletBox[0]->Init("Bullet.png", "Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
	else if (Constant::GetInstance()->GetAttackLevel() == GameStats::DOUBLEROUND)
	{
		bulletBox[0]->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f-20, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
		bulletBox[1]->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f+20, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);

		bulletBox[1]->SetShoot(e->getLocationInView());
		bulletBox[1]->BulletMove();

		moveableItems->addChild(bulletBox[1], 1);
	}
	else if (Constant::GetInstance()->GetAttackLevel() == GameStats::TRIPLEROUND)
	{
		bulletBox[0]->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 25, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
		bulletBox[1]->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);
		bulletBox[2]->Init("Bullet.png", "3Bullets", visibleSize.width * 0.5f + 25, (visibleSize.height - playingSize.height), 0, dir.x, dir.y);

		bulletBox[1]->SetShoot(e->getLocationInView());
		bulletBox[1]->BulletMove();
		bulletBox[2]->SetShoot(e->getLocationInView());
		bulletBox[2]->BulletMove();

		moveableItems->addChild(bulletBox[1], 1);
		moveableItems->addChild(bulletBox[2], 1);
	}
	else if (Constant::GetInstance()->GetAttackLevel() == GameStats::SPLITROUND)
	{
		bulletBox[0]->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 25, (visibleSize.height - playingSize.height), -45, dir.x, dir.y);
		bulletBox[1]->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), 90, dir.x, dir.y);
		bulletBox[2]->Init("Bullet.png", "3Bullets", visibleSize.width * 0.5f + 25, (visibleSize.height - playingSize.height), 45, dir.x, dir.y);
		
		bulletBox[1]->SetShoot(e->getLocationInView());
		bulletBox[1]->BulletMove();
		bulletBox[2]->SetShoot(e->getLocationInView());
		bulletBox[2]->BulletMove();

		moveableItems->addChild(bulletBox[1], 1);
		moveableItems->addChild(bulletBox[2], 1);
	}

	bulletBox[0]->SetShoot(e->getLocationInView());
	bulletBox[0]->BulletMove();

	//m_Bullets.push_back(proBullet);

	// Add Bullets to Movable
	moveableItems->addChild(bulletBox[0], 1);
	b_mouseclicked = true;
}

void HelloWorld::onMouseDown(Event * mouse)
{
	
}

void HelloWorld::onMouseScroll(Event * mouse)
{
}

void HelloWorld::onTouchMove(Event * Touch)
{
	/*EventTouch* eventTouch = static_cast<EventTouch*>(Touch);
	EventTouch *e = (EventTouch*)Touch;

	mainCharacter.SetCharAim(e->getCurrentTarget()->getPosition());*/
}

void HelloWorld::JustShoot()
{
	float rot = mainCharacter.getSprite()->getRotation();

	//GameBullet* proBullet = new GameBullet();
	//GameBullet* bullet = new GameBullet();
	//GameBullet* thiBullet = new GameBullet();

	//if (Constant::GetInstance()->GetAttackLevel() == GameStats::SINGLEROUND)
	//	proBullet->Init("Bullet.png", "Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), rot-90);
	//else if (Constant::GetInstance()->GetAttackLevel() == GameStats::DOUBLEROUND)
	//{
	//	proBullet->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 20, (visibleSize.height - playingSize.height), rot - 90);
	//	bullet->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f + 20, (visibleSize.height - playingSize.height), rot - 90);

	//	bullet->BulletMove();

	//	moveableItems->addChild(bullet, 1);
	//}
	//else if (Constant::GetInstance()->GetAttackLevel() == GameStats::TRIPLEROUND)
	//{
	//	proBullet->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 25, (visibleSize.height - playingSize.height), rot - 90);
	//	bullet->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), rot - 90);
	//	thiBullet->Init("Bullet.png", "3Bullets", visibleSize.width * 0.5f + 25, (visibleSize.height - playingSize.height), rot - 90);

	//	bullet->BulletMove();
	//	thiBullet->BulletMove();

	//	moveableItems->addChild(bullet, 1);
	//	moveableItems->addChild(thiBullet, 1);
	//}
	//else if (Constant::GetInstance()->GetAttackLevel() == GameStats::SPLITROUND)
	//{
	//	proBullet->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 25, (visibleSize.height - playingSize.height), rot-45);
	//	bullet->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), rot - 90);
	//	thiBullet->Init("Bullet.png", "3Bullets", visibleSize.width * 0.5f + 25, (visibleSize.height - playingSize.height), rot-135);

	//	bullet->BulletMove();
	//	thiBullet->BulletMove();

	//	moveableItems->addChild(thiBullet, 1);
	//	moveableItems->addChild(bullet, 1);
	//}
	//proBullet->BulletMove();
	//moveableItems->addChild(proBullet, 1);


	int bulletSize = (int)Constant::GetInstance()->GetAttackLevel() + 1;
	std::vector<GameBullet*> bulletBox;

	for (size_t i = 0; i < bulletSize; i++)
	{
		if (i == 3)
			break;

		bulletBox.push_back(new GameBullet());
	}

	if (Constant::GetInstance()->GetAttackLevel() == GameStats::SINGLEROUND)
		bulletBox[0]->Init("Bullet.png", "Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), rot - 90);
	else if (Constant::GetInstance()->GetAttackLevel() == GameStats::DOUBLEROUND)
	{
		bulletBox[0]->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 20, (visibleSize.height - playingSize.height), rot - 90);
		bulletBox[1]->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f + 20, (visibleSize.height - playingSize.height), rot - 90);

		//bulletBox[1]->SetShoot(e->getLocationInView());
		bulletBox[1]->BulletMove();

		moveableItems->addChild(bulletBox[1], 1);
	}
	else if (Constant::GetInstance()->GetAttackLevel() == GameStats::TRIPLEROUND)
	{
		bulletBox[0]->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 25, (visibleSize.height - playingSize.height), rot - 90);
		bulletBox[1]->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), rot - 90);
		bulletBox[2]->Init("Bullet.png", "3Bullets", visibleSize.width * 0.5f + 25, (visibleSize.height - playingSize.height), rot - 90);

		//bulletBox[1]->SetShoot(e->getLocationInView());
		bulletBox[1]->BulletMove();
		//bulletBox[2]->SetShoot(e->getLocationInView());
		bulletBox[2]->BulletMove();

		moveableItems->addChild(bulletBox[1], 1);
		moveableItems->addChild(bulletBox[2], 1);
	}
	else if (Constant::GetInstance()->GetAttackLevel() == GameStats::SPLITROUND)
	{
		bulletBox[0]->Init("Bullet.png", "1Bullets", visibleSize.width * 0.5f - 25, (visibleSize.height - playingSize.height), rot - 45);
		bulletBox[1]->Init("Bullet.png", "2Bullets", visibleSize.width * 0.5f, (visibleSize.height - playingSize.height), rot - 90);
		bulletBox[2]->Init("Bullet.png", "3Bullets", visibleSize.width * 0.5f + 25, (visibleSize.height - playingSize.height), rot - 135);

		//bulletBox[1]->SetShoot(e->getLocationInView());
		bulletBox[1]->BulletMove();
		//bulletBox[2]->SetShoot(e->getLocationInView());
		bulletBox[2]->BulletMove();

		moveableItems->addChild(bulletBox[1], 1);
		moveableItems->addChild(bulletBox[2], 1);
	}

	//bulletBox[0]->SetShoot(e->getLocationInView());
	bulletBox[0]->BulletMove();

	//m_Bullets.push_back(proBullet);

	// Add Bullets to Movable
	moveableItems->addChild(bulletBox[0], 1);
	b_mouseclicked = true;
}



