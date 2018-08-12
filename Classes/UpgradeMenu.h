#ifndef __UPGRADEMENU_SCENE_H__
#define __UPGRADEMENU_SCENE_H__

#include "cocos2d.h"
#include "../cocos2d/cocos/ui/CocosGUI.h"

using namespace cocos2d::ui;
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

	Button* upgradeBuilding_0;
	Button* upgradeBuilding_0_Up;
	Button* upgradeBuilding_1;
	Button* upgradeBuilding_1_Up;
	Button* upgradeBuilding_2;
	Button* upgradeBuilding_2_Up;

	Button* upgradeWeapon_0;
	Button* upgradeWeapon_0_Up;
	Button* upgradeWeapon_1;
	Button* upgradeWeapon_1_Up;
	Button* upgradeWeapon_2;
	Button* upgradeWeapon_2_Up;
	Button* upgradeWeapon_3;
	Button* upgradeWeapon_3_Up;

	Button* upgradeHealth_0;
	Button* upgradeHealth_0_Up;
	Button* upgradeHealth_1;
	Button* upgradeHealth_1_Up;
	Button* upgradeHealth_2;
	Button* upgradeHealth_2_Up;
	Button* upgradeHealth_3;
	Button* upgradeHealth_3_Up;

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
