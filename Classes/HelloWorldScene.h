#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Buildings.h"
#include "Humans.h"
#include "WaveSpawner.h"
#include "GameStats.h"
#include "../cocos2d/cocos/ui/CocosGUI.h"

using namespace cocos2d::ui;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	bool OnContactBegin(cocos2d::PhysicsContact &contact);



	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	//virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);

	virtual void onMouseMove(Event* mouse);
	virtual void onMouseUp(Event* mouse);
	virtual void onMouseDown(Event* mouse);
	virtual void onMouseScroll(Event* mouse);

	virtual void onTouchMove(Event* Touch);
	void JustShoot();
	bool b_mouseclicked = false;
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	float elapseTime;
private:
	Node* moveableItems;
	Node* moveableItems2;

	GameChar mainCharacter;

	GameHumans males;
	GameHumans females;

	int asteroidsCount;
	float spawnTimer;
	Size visibleSize;
	Size playingSize;

	WaveSpawner spawner;

	int scoreNum;
	Label* label;

	ProgressTimer *progressTimer;
};

#endif // __HELLOWORLD_SCENE_H__
