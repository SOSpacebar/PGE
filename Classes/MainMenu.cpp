#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "Constants.h"
#include "AudioManager.h"
#include "../cocos2d/cocos/ui/CocosGUI.h"
#ifdef SDKBOX_ENABLED
#include <PluginFaceBook/PluginFacebook.h>
#endif // #define CC_PlatForm_IOS
using namespace cocos2d::ui;

USING_NS_CC;

Scene* MainMenu::createScene()
{
	auto scene = MainMenu::create();

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
bool MainMenu::init()
{
    // Logout Facebook
#ifdef SDKBOX_ENABLED
    sdkbox::PluginFacebook::logout();
#endif
    
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
	auto background = Sprite::create("MainMenu2.png");

	// Load Main Sprite
	std::vector<GameHumans*> humans;

	for (size_t i = 0; i < 4; i++)
	{
		humans.push_back(new GameHumans);
	}
	humans[0]->Init("Humans/Man_Right_1.png", "maleSprite", 0, visibleSize.height * 0.05f, 2, -6, 0);
	humans[1]->Init("Humans/Female_Right_1.png", "femaleSprite", visibleSize.width , visibleSize.height * 0.05f, 2, -6, 1);
	humans[2]->Init("Humans/Man_Right_1.png", "maleSprite", visibleSize.width*0.5f, visibleSize.height * 0.25f, 4, -5, 0);
	humans[3]->Init("Humans/Female_Right_1.png", "femaleSprite", visibleSize.width*0.5f, visibleSize.height * 0.25f, 4, -5, 1);
	
	//humans[0]->setScaleY(-3);
	//humans[0]->setScaleX(-3);
	//humans[1]->setScaleY(-3);
	//humans[1]->setScaleX(-3);
	//humans[2]->setScaleY(-3);
	//humans[2]->setScaleX(-3);
	//humans[3]->setScaleY(-3);
	//humans[3]->setScaleX(-3);


	nodeItems->addChild(humans[0], 1);
	nodeItems->addChild(humans[1], 1);
	nodeItems->addChild(humans[2], 1);
	nodeItems->addChild(humans[3], 1);
	
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

	float bS = 1.2f;
	int bX = (visibleSize.width - playingSize.width) - (background->getContentSize().width/5.f);
	int bY = (visibleSize.height - playingSize.height)- (background->getContentSize().height*0.15);

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

	// Set into Constants
	Constant::GetInstance()->SetVisableSize(visibleSize);

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
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MainMenu::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// Mouse Event
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(MainMenu::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(MainMenu::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MainMenu::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(MainMenu::onMouseScroll, this);
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

	auto Start = Button::create("Start.png", "StartPress.png");
	Start->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height - Start->getContentSize().height) / 2));
	Start->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::ENDED:
			SceneManager::GetInstance()->RunSceneWithType(SceneType::LOADING, TransitionType::CROSSFADE);
			break;
		default:
			break;
		}
	});
	this->addChild(Start, 2);

	//auto Upgrade = Button::create("Upgrade.png", "UpgradePress.png");
	//Upgrade->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	(origin.y + visibleSize.height - Upgrade->getContentSize().height) / 2.5));
	//Upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	//{
	//	switch (type)
	//	{
	//	case Widget::TouchEventType::BEGAN:
	//		break;
	//	case Widget::TouchEventType::ENDED:
	//		SceneManager::GetInstance()->RunSceneWithType(SceneType::UPGRADESCENE, TransitionType::CROSSFADE);
	//		break;
	//	default:
	//		break;
	//	}
	//});
	//this->addChild(Upgrade, 2);

	auto Setting = Button::create("Settings.png", "SettingPress.png");
	Setting->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height - Setting->getContentSize().height) / 3));
	Setting->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::ENDED:
			SceneManager::GetInstance()->RunSceneWithType(SceneType::SETTING, TransitionType::CROSSFADE);
			break;
		default:
			break;
		}
	});
	this->addChild(Setting, 2);

	auto Exit = Button::create("Exit.png", "ExitPress.png");
	Exit->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height - Exit->getContentSize().height) / 5.5));
	Exit->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::ENDED:
			CCDirector::sharedDirector()->end();
			break;
		default:
			break;
		}
	});
	this->addChild(Exit, 2);
    
    //FaceBook
    auto fbButton = Button::create("Fb.png", "Fb.png");
	fbButton->setScale(0.4f);
    fbButton->setPosition(Vec2(origin.x + visibleSize.width / 15,
                           (origin.y + visibleSize.height - fbButton->getContentSize().height) / 0.75));
    fbButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
                                {
                                    switch (type)
                                    {
                                        case Widget::TouchEventType::BEGAN:
                                        {
                                            break;
                                        }
                                        case Widget::TouchEventType::ENDED:

#ifdef SDKBOX_ENABLED
                                            if (!sdkbox::PluginFacebook::isLoggedIn()){
                                                sdkbox::PluginFacebook::login();
                                            }
                                            
                                            sdkbox::FBShareInfo info;
                                            info.type = sdkbox::FB_LINK;
                                            info.title = "Raining Asteroids";
                                            info.link = "https://www.facebook.com/hayashikiyoi";
                                            info.text = "Wow, I've just got a high score of 0";
                                            sdkbox::PluginFacebook::dialog(info);
#endif
                                            break;
                                    }
                                });
    this->addChild(fbButton, 2);
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

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}

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


void MainMenu::menuCloseCallback(Ref* pSender)
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

void MainMenu::update(float delta)
{
	//mainCharacter.Update(delta);
	//males.update(delta);
	//females.update(delta);
	//smallMales.update(delta);
	//smallFemales.update(delta);
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

void MainMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
	default:
		break;
	}

	log("Key with keycode %d pressed", keyCode);
}

void MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//mainCharacter.MoveChar(EAction::eStop);
	log("Key with keycode %d released", keyCode);
}

void MainMenu::onMouseMove(Event * mouse)
{
	EventMouse* eventMouse = static_cast<EventMouse*>(mouse);
	EventMouse *e = (EventMouse*)mouse;

	//mainCharacter.SetCharAim(eventMouse->getLocationInView());
	/*if (!b_mouseclicked)
		Bullet.SetShoot(eventMouse->getLocationInView());*/
}

void MainMenu::onMouseUp(Event * mouse)
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

void MainMenu::onMouseDown(Event * mouse)
{
	
}

void MainMenu::onMouseScroll(Event * mouse)
{
}

