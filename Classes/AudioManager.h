#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

class AudioManager
{
public:
	void MusicPlay(std::string file, bool loop = true);
	void MusicStop();
	void MusicPause();

	void SFXPlay(std::string file);

	static AudioManager* GetInstance();
	~AudioManager();

protected:
	AudioManager();
	static AudioManager * _instance;

	int _backgroundMusicId;
public:

};
#endif 