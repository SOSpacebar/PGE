#include "SceneManager.h"
#include "MainMenu.h"
#include "UpgradeMenu.h"
#include "Settings.h"
#include "LoseMenu.h"
#include "WinMenu.h"
#include "HelloWorldScene.h"
#include "LoadingScene.h"
#include "AudioManager.h"

// Singleton
SceneManager * SceneManager::_instance = NULL;


SceneManager* SceneManager::GetInstance()
{
	if (!_instance) _instance = new SceneManager();
	return _instance;
}

SceneManager::SceneManager() :
	_sceneTypeToReturn(SceneType::NONE),
	_currentSceneType(SceneType::MAINMENU)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::RunSceneWithType(const SceneType sceneType, const TransitionType tType)
{
	if (_sceneTypeToReturn == sceneType)
		return;

	Scene *sceneToRun = nullptr;

	switch (sceneType) {
	case SceneType::MAINMENU:
		sceneToRun = MainMenu::createScene();
		AudioManager::GetInstance()->PreLoadAudioByScene(SceneType::MAINMENU);
		break;
	case SceneType::GAMEPLAY:
		sceneToRun = HelloWorld::createScene();
		AudioManager::GetInstance()->PreLoadAudioByScene(SceneType::GAMEPLAY);
		break;
	case SceneType::LOADING:
		sceneToRun = LoadingScene::createScene();
		AudioManager::GetInstance()->PreLoadAudioByScene(SceneType::LOADING);
		break;
	case SceneType::UPGRADESCENE:
		sceneToRun = UpgradeMenu::createScene();
		AudioManager::GetInstance()->PreLoadAudioByScene(SceneType::UPGRADESCENE);
		break;
	case SceneType::WINSCENE:
		sceneToRun = WinMenu::createScene();
		AudioManager::GetInstance()->PreLoadAudioByScene(SceneType::WINSCENE);
		break;
	case SceneType::LOSESCENE:
		sceneToRun = LoseMenu::createScene();
		AudioManager::GetInstance()->PreLoadAudioByScene(SceneType::LOSESCENE);
		break;
	case SceneType::SETTING:
		sceneToRun = Settings::createScene();
		AudioManager::GetInstance()->PreLoadAudioByScene(SceneType::SETTING);
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