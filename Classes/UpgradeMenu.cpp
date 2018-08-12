#include "UpgradeMenu.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "Constants.h"
#include "AudioManager.h"
#include "../cocos2d/cocos/ui/CocosGUI.h"

using namespace cocos2d::ui;

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

	auto background = Sprite::create("UpgradeMenu.png");

	background->setAnchorPoint(Vec2::ZERO);


	float bS = 1.0f;
	int bX = (visibleSize.width - playingSize.width) - (background->getContentSize().width/360.0f);
	int bY = (visibleSize.height - playingSize.height)- (background->getContentSize().height*0.125f);

	auto newBackgroundNode = Sprite::createWithSpriteFrame(background->getSpriteFrame());
	newBackgroundNode->setAnchorPoint(Vec2::ZERO);
	newBackgroundNode->setPosition(bX, bY);
	newBackgroundNode->setScale(bS);
	bX += newBackgroundNode->getContentSize().width;
	nodeItems->addChild(newBackgroundNode, -1);

	this->addChild(nodeItems, 1);

	//PLAY MUSIC
	AudioManager::GetInstance()->MusicPlay("BGM_Main", true);

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
   
	upgradeTitleText = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	upgradeTitleText->setPosition(Vec2(origin.x + visibleSize.width / 1.4, origin.y + visibleSize.height / 1.2 + origin.y));
	upgradeTitleText->setColor(Color3B(255, 255, 255));
	this->addChild(upgradeTitleText, 1);

	upgradeText = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	upgradeText->setPosition(Vec2(origin.x + visibleSize.width / 1.4, origin.y + visibleSize.height / 1.6 + origin.y));
	upgradeText->setColor(Color3B(255, 255, 255));
	this->addChild(upgradeText, 1);

	//Label Settings
	auto label = Label::createWithTTF("Upgrade", "fonts/Marker Felt.ttf", 30);
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height * 0.85));
	label->setColor(Color3B(0, 0, 0));
	// add the label as a child to this layer
	this->addChild(label, 1);


	/*************************************************

	Building UPGRADE SECTIONS

	*************************************************/
	auto upgradeBuilding_0 = Button::create("BuildingUpgrade.png", "BuildingUpgradeComplete.png", "BuildingUpgradeComplete.png");
	upgradeBuilding_0->setScale(1.25, 1.25);
	upgradeBuilding_0->setPosition(Vec2(origin.x + visibleSize.width / 6, origin.y + visibleSize.height / 1.35 + origin.y));
	upgradeBuilding_0->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Building Upgrade Level 1");
			upgradeText->setString("More Income will get from the level fight");
			break;
		case Widget::TouchEventType::ENDED:

			break;
		default:
			break;
		}
	});
	this->addChild(upgradeBuilding_0, 2);

	auto upgradeBuilding_1 = Button::create("BuildingUpgrade2Locked.png", "BuildingUpgrade2.png", "BuildingUpgrade2Complete.png");
	upgradeBuilding_1->setScale(1.25, 1.25);
	upgradeBuilding_1->setPosition(Vec2(origin.x + visibleSize.width / 3.5, origin.y + visibleSize.height / 1.25 + origin.y));
	upgradeBuilding_1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Building Upgrade Level 2v1");
			upgradeText->setString("More and More income will be able to get");
			break;
		case Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeBuilding_1, 2);

	auto upgradeBuilding_2 = Button::create("BuildingUpgrade2Locked.png", "BuildingUpgrade2.png", "BuildingUpgrade2Complete.png");
	upgradeBuilding_2->setScale(1.25, 1.25);
	upgradeBuilding_2->setPosition(Vec2(origin.x + visibleSize.width / 3.5, origin.y + visibleSize.height / 1.45 + origin.y));
	upgradeBuilding_2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Building Upgrade Level 2v2");
			upgradeText->setString("More Income and Minimum \n health recovery increase");
			break;
		case Widget::TouchEventType::ENDED:
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
	upgradeWeapon_0->setScale(1.25, 1.25);
	upgradeWeapon_0->setPosition(Vec2(origin.x + visibleSize.width / 6, origin.y + visibleSize.height / 2.25 + origin.y));

	upgradeWeapon_0->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Bullet Upgrade Level 1");
			upgradeText->setString("First Upgrade \n stronger missle on the run");
			break;
		case Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeWeapon_0, 2);
	
	auto upgradeWeapon_1 = Button::create("BulletUpgrade2Locked.png", "BulletUpgrade2.png", "BulletUpgrade2Complete.png");
	upgradeWeapon_1->setScale(1.25, 1.25);
	upgradeWeapon_1->setPosition(Vec2(origin.x + visibleSize.width / 3.5, origin.y + visibleSize.height / 2.25 + origin.y));
	upgradeWeapon_1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Bullet Upgrade Level 2");
			upgradeText->setString("Double the missle!!!!! \n Double the fun!!!!");
			Constant::GetInstance()->SetAttackLevel(GameStats::PlayerAttackLevel::DOUBLEROUND);
			break;
		case Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeWeapon_1, 2);

	auto upgradeWeapon_2 = Button::create("BulletUpgrade3Locked.png", "BulletUpgrade3.png", "BulletUpgrade3Complete.png");
	upgradeWeapon_2->setScale(1.25, 1.25);
	upgradeWeapon_2->setPosition(Vec2(origin.x + visibleSize.width / 2.5, origin.y + visibleSize.height / 2 + origin.y));
	upgradeWeapon_2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Bullet Upgrade Level 3v2");
			upgradeText->setString("Triple the missle!!!!! \n More focus on one direction and \n damage on one enemy increase more stronger");
			Constant::GetInstance()->SetAttackLevel(GameStats::PlayerAttackLevel::TRIPLEROUND);
			break;
		case Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeWeapon_2, 2);

	auto upgradeWeapon_3 = Button::create("BulletUpgrade4Locked.png", "BulletUpgrade4.png", "BulletUpgrade4sComplete.png");
	upgradeWeapon_3->setScale(1.25, 1.25);
	upgradeWeapon_3->setPosition(Vec2(origin.x + visibleSize.width / 2.5, origin.y + visibleSize.height / 2.6 + origin.y));
	upgradeWeapon_3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Bullet Upgrade Level 3v1");
			upgradeText->setString("Triple the missle!!!!! \n Hit Omnidirection to all enemy around it");
			Constant::GetInstance()->SetAttackLevel(GameStats::PlayerAttackLevel::SPLITROUND);
			break;
		case Widget::TouchEventType::ENDED:
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
	upgradeHealth_0->setScale(1.25, 1.25);
	upgradeHealth_0->setPosition(Vec2(origin.x + visibleSize.width / 6, origin.y + visibleSize.height / 5.5 + origin.y));
	upgradeHealth_0->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Health Upgrade Level 1");
			upgradeText->setString("More Health increase in the game");
			Constant::GetInstance()->SetHealthLevel(GameStats::PlayerHealthLevel::HEALTHLEVEL1);
			break;
		case Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeHealth_0, 2);

	auto upgradeHealth_1 = Button::create("HealthIncrease2Locked.png", "HealthIncrease2.png","HealthIncrease2Complete.png");
	upgradeHealth_1->setScale(1.25, 1.25);
	upgradeHealth_1->setPosition(Vec2(origin.x + visibleSize.width / 3.5, origin.y + visibleSize.height / 5.5 + origin.y));
	upgradeHealth_1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Health Upgrade Level 2");
			upgradeText->setString("More and More Health increase in the game");
			Constant::GetInstance()->SetHealthLevel(GameStats::PlayerHealthLevel::HEALTHLEVEL2);
			break;
		case Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeHealth_1, 2);

	auto upgradeHealth_2 = Button::create("HealthIncrease2Locked.png", "HealthIncrease2.png", "HealthIncrease2Complete.png");
	upgradeHealth_2->setScale(1.25, 1.25);
	upgradeHealth_2->setPosition(Vec2(origin.x + visibleSize.width / 2.5, origin.y + visibleSize.height / 4 + origin.y));
	upgradeHealth_2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Health Upgrade Level 3v1");
			upgradeText->setString("Recovery Overtime");
			Constant::GetInstance()->SetHealthLevel(GameStats::PlayerHealthLevel::HEALTHLEVEL3_1);
			break;
		case Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeHealth_2, 2);

	auto upgradeHealth_3 = Button::create("HealthIncrease2Locked.png", "HealthIncrease2.png", "HealthIncrease2Complete.png");
	upgradeHealth_3->setScale(1.25, 1.25);
	upgradeHealth_3->setPosition(Vec2(origin.x + visibleSize.width / 2.5, origin.y + visibleSize.height / 8 + origin.y));
	upgradeHealth_3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			upgradeTitleText->setString("Health Upgrade Level 3v2");
			upgradeText->setString("Health Increase x3");
			Constant::GetInstance()->SetHealthLevel(GameStats::PlayerHealthLevel::HEALTHLEVEL3_2);
			break;
		case Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(upgradeHealth_3, 2);

	// OTHERS
	auto Back = Button::create("Back.png", "BackPress.png");
	Back->setScale(1, 1);
	Back->setPosition(Vec2(origin.x + visibleSize.width / 14.5, origin.y + visibleSize.height / 1.13 + origin.y));
	Back->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::ENDED:
			SceneManager::GetInstance()->RunSceneWithType(SceneType::MAINMENU, TransitionType::CROSSFADE);
			break;
		default:
			break;
		}
	});
	this->addChild(Back, 2);

	auto NewStage = Button::create("Back.png", "BackPress.png");
	NewStage->setRotation(180);
	NewStage->setScale(1, 1);
	NewStage->setPosition(Vec2(origin.x + visibleSize.width / 1.08, origin.y + visibleSize.height / 1.13 + origin.y));
	NewStage->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::ENDED:
			SceneManager::GetInstance()->RunSceneWithType(SceneType::GAMEPLAY, TransitionType::CROSSFADE);
			break;
		default:
			break;
		}
	});
	this->addChild(NewStage, 2);

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
	log("Key with keycode %d released", keyCode);
}

void UpgradeMenu::onMouseMove(Event * mouse)
{
	EventMouse* eventMouse = static_cast<EventMouse*>(mouse);
	EventMouse *e = (EventMouse*)mouse;
}

void UpgradeMenu::onMouseUp(Event * mouse)
{
	EventMouse* eventMouse = static_cast<EventMouse*>(mouse);
	EventMouse *e = (EventMouse*)mouse;

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

