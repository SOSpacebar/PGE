#include "AudioManager.h"

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
	if (!_instance) _instance = new AudioManager();
	return _instance;
}

AudioManager::AudioManager() :
	_backgroundMusicId(-1)
{

}

AudioManager::~AudioManager()
{

}

void AudioManager::MusicPlay(std::string file, bool loop)
{
	std::string path;
	path = "audio/" + file + audioExtension;
	if (_backgroundMusicId > -1) {
		this->MusicStop();
	}
	_backgroundMusicId = AudioEngine::play2d(path, loop);
}

void AudioManager::MusicStop()
{
	AudioEngine::stop(_backgroundMusicId);
	_backgroundMusicId = -1;
}

void AudioManager::MusicPause()
{
	AudioEngine::pause(_backgroundMusicId);
}

void AudioManager::SFXPlay(std::string file)
{
	std::string path;
	path = "audio/" + file + audioExtension;
	AudioEngine::play2d(path);
}