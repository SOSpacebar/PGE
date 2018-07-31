#ifndef __UPGRADEMENU_SCENE_H__
#define __UPGRADEMENU_SCENE_H__

#include "cocos2d.h"
//#include "Humans.h"
//#include "Bullet.h"
//#include "Asteroid.h"

using namespace cocos2d;
using namespace ui;
class UpgradeMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);



	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);

	virtual void onMouseMove(Event* mouse);
	virtual void onMouseUp(Event* mouse);
	virtual void onMouseDown(Event* mouse);
	virtual void onMouseScroll(Event* mouse);
	virtual void onButtonClick();

	bool b_mouseclicked = false;
	// implement the "static create()" method manually
    CREATE_FUNC(UpgradeMenu);

private:
	//GameHumans males;
	//GameHumans females;
	//int asteroidsCount;
	//float SpawnTimer;
	Size gameSize; 
	Size visibleSize;
	Size playingSize;
	Label* upgradeTitleText;
	Label* upgradeText;
};

#endif // __UpgradeMenu_SCENE_H__
