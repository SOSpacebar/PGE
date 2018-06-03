#include "SceneManager.h"
#include "MainMenu.h"
#include "HelloWorldScene.h"
#include "LoadingScene.h"

// Singleton
SceneManager * SceneManager::_instance = NULL;


SceneManager* SceneManager::GetInstance()
{
	if (!_instance) _instance = new SceneManager();
	return _instance;
}

SceneManager::SceneManager() :
	_sceneTypeToReturn(SceneType::MAINMENU),
	_currentSceneType(SceneType::MAINMENU)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::RunSceneWithType(const SceneType sceneType, const TransitionType tType)
{
	Scene *sceneToRun = nullptr;

	switch (sceneType) {
	case SceneType::MAINMENU:
		sceneToRun = MainMenu::createScene();
		break;
	case SceneType::GAMEPLAY:
		sceneToRun = HelloWorld::createScene();
		break;
	case SceneType::LOADING:
		sceneToRun = LoadingScene::createScene();
		break;
	default:
		log("WARNING! Default value when trying to run scene with id %d", static_cast<int>(sceneType));
		return;
		break;
	}

	SceneType oldScene = _currentSceneType;
	_currentSceneType = sceneType;
	sceneToRun->setTag(static_cast<int>(sceneType));

	if (sceneToRun == nullptr) {
		_currentSceneType = oldScene;
		return;
	}

	_sceneTypeToReturn = oldScene;

	switch (tType)
	{
		case TransitionType::NORMAL:
		{
			if (CCDirector::getInstance()->getRunningScene() == nullptr) {
				CCDirector::getInstance()->runWithScene(sceneToRun);
			}
			else {
				CCDirector::getInstance()->replaceScene(sceneToRun);
			}
		}
		break;
		case TransitionType::FADE:
		{
			if (CCDirector::getInstance()->getRunningScene() == nullptr) {
				CCDirector::getInstance()->runWithScene(TransitionFade::create(1.5f, sceneToRun));
			}
			else {
				CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5f, sceneToRun));
			}
		}
		break;
		case TransitionType::CROSSFADE:
		{
			if (CCDirector::getInstance()->getRunningScene() == nullptr) {
				CCDirector::getInstance()->runWithScene(TransitionCrossFade::create(1.5f, sceneToRun));
			}
			else {
				CCDirector::getInstance()->replaceScene(TransitionCrossFade::create(1.5f, sceneToRun));
			}
		}
		break;
		default:
			break;
	}
	
}

void SceneManager::ReturnToLastScene()
{
	this->RunSceneWithType(_sceneTypeToReturn);
}