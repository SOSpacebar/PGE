#include "AudioManager.h"
#include "SimpleAudioEngine.h"

// Singleton
AudioManager * AudioManager::_instance = NULL;

/**
* Declare sound extension for each platform
* Android = ogg
* iOS = caf
* WIN32 = mp3
*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static std::string audioExtension = ".mp3";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
static std::string audioExtension = ".caf";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static std::string audioExtension = ".ogg";
#endif

AudioManager* AudioManager::GetInstance()
{
	if (!_instance) 
		_instance = new AudioManager();
	return _instance;
}

AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{
	if (_instance)
	{
		delete _instance;
		_instance = 0;
	}
}

void AudioManager::MusicPlay(std::string file, bool loop)
{
	std::string path;
	path = "audio/" + file + audioExtension;
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic(path.c_str(), loop);
}

void AudioManager::MusicStop()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
}

void AudioManager::MusicPause()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->pauseBackgroundMusic();
}

void AudioManager::SFXPlay(std::string file, bool loop)
{
	std::string path;
	path = "audio/" + file + audioExtension;

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect(path.c_str(), loop);
}

void AudioManager::SFXPause()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->pauseAllEffects();
}

void AudioManager::SFXStop()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopAllEffects();
}

void AudioManager::PreLoadAudio(std::string file, bool isBGM)
{
	std::string path;
	path = "audio/" + file + audioExtension;
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	if (isBGM)
		audio->preloadBackgroundMusic(path.c_str());
	else
		audio->preloadEffect(path.c_str());

}

void AudioManager::PreLoadAudioByScene(SceneType scene)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	switch (scene)
	{
	case SceneType::NONE:
		break;
	case SceneType::MAINMENU:
		audio->preloadBackgroundMusic("audio/BGM_Main.mp3");
		break;
	case SceneType::GAMEPLAY:
		audio->preloadEffect("audio/SFX_Rocket.mp3");
		break;
	case SceneType::LOADING:
		break;
	default:
		break;
	}
}

void AudioManager::UnLoadAudio(std::string file)
{
	std::string path;
	path = "audio/" + file + audioExtension;
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	audio->unloadEffect(path.c_str());
}

void AudioManager::UnLoadAudioByScene(SceneType scene)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	switch (scene)
	{
	case SceneType::NONE:
		break;
	case SceneType::MAINMENU:
		break;
	case SceneType::GAMEPLAY:
		break;
	case SceneType::LOADING:
		break;
	default:
		break;
	}
}
