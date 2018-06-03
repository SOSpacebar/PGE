#ifndef LOADING_SCENE_H
#define LOADING_SCENE_H

#include "cocos2d.h"
#include "Character.h"
//#include "Bullet.h"
//#include "Asteroid.h"

using namespace cocos2d;

class LoadingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void LoadingTextureFinished(Texture2D* texture);


	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);

	virtual void onMouseMove(Event* mouse);
	virtual void onMouseUp(Event* mouse);
	virtual void onMouseDown(Event* mouse);
	virtual void onMouseScroll(Event* mouse);

	bool b_mouseclicked = false;
	// implement the "static create()" method manually
	CREATE_FUNC(LoadingScene);

private:
	Size visibleSize;
	Size playingSize;

	float percent;
	ProgressTimer *progressTimer;
};

#endif
