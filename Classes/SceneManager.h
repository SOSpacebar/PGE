#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "cocos2d.h"
#include "Classes\Constants.h"

using namespace cocos2d;

class SceneManager
{
public:	// Public singleton
	static SceneManager* GetInstance();
	~SceneManager();
	void RunSceneWithType(const SceneType sceneType, const TransitionType tType = TransitionType::NORMAL);
	void ReturnToLastScene();
private:
	SceneType _sceneTypeToReturn;
	SceneType _currentSceneType;
	static SceneManager * _instance;
	SceneManager();
};

#endif // !
