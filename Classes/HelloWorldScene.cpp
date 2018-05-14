#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = HelloWorld::create();

	//// 'layer' is an autorelease object
	//auto layer = HelloWorld::create();

	//// add layer as a child to scene
	//scene->addChild(layer, 999);

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
    if ( !Scene::init() )
    {
        return false;
    }

	this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Playing Size
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	// Node container for non-moveable sprites
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	// Node container for moveable sprites
	auto moveableItems = Node::create();
	moveableItems->setName("moveableItems");

	// Create a sprite object to load the image
	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");

	// Load Main Sprite
	mainCharacter.Init("Blue_Front1.png", "mainSprite", 100, (visibleSize.height - playingSize.height));
	//auto mainSprite = Sprite::create("Blue_Front1.png");
	//mainSprite->setAnchorPoint(Vec2(0, 0));
	//mainSprite->setPosition(100, (visibleSize.height - playingSize.height));
	//mainSprite->setName("mainSprite");

	// Set anchor point and position of object
	sprite->setAnchorPoint(Vec2::ZERO);
	//sprite->setPosition(0, 0);

	

	// Add object into the node container
	int loopSize = std::ceil(visibleSize.width / sprite->getContentSize().width);
	int sX = 0;
	int sY = (visibleSize.height - playingSize.height) - sprite->getContentSize().height;

	for (size_t i = 0; i < loopSize; ++i)
	{
		auto newNode = Sprite::createWithSpriteFrame(sprite->getSpriteFrame());
		newNode->setAnchorPoint(Vec2::ZERO);
		newNode->setPosition(sX, sY);
		sX += newNode->getContentSize().width;

		nodeItems->addChild(newNode, 0);
	}

	// Add mainSprite to moveable
	moveableItems->addChild(mainCharacter.getSprite(), 1);

	// Add the note container into the scene graph
	this->addChild(nodeItems, 1);
	this->addChild(moveableItems, 1);

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

void HelloWorld::update(float delta)
{
	mainCharacter.Update(delta);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		mainCharacter.MoveChar(EAction::eRight);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		mainCharacter.MoveChar(EAction::eLeft);
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
}

void HelloWorld::onMouseUp(Event * mouse)
{
}

void HelloWorld::onMouseDown(Event * mouse)
{
	EventMouse *e = (EventMouse*)mouse;
	mainCharacter.MoveCharByCoord(e->getCursorX(), e->getCursorY());
}

void HelloWorld::onMouseScroll(Event * mouse)
{
}

