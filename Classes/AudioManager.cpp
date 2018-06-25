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