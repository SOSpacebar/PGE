#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "cocos2d.h"
#include "Constants.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

class AudioManager
{
public:
	void MusicPlay(std::string file, bool loop = true);
	void MusicStop();
	void MusicPause();

	void SFXPlay(std::string file, bool loop = false);
	void SFXStop();
	void SFXPause();

	void PreLoadAudio(std::string file, bool isBGM = false);
	void PreLoadAudioByScene(SceneType scene);

	void UnLoadAudio(std::string file);
	void UnLoadAudioByScene(SceneType scene);


	static AudioManager* GetInstance();
	~AudioManager();

protected:
	AudioManager();
	static AudioManager * _instance;
public:

};
#endif 