#ifndef CONSTANT_H
#define CONSTANT_H

#include "cocos2d.h"

using namespace cocos2d;

enum class SceneType
{
	NONE,
	MAINMENU,
	GAMEPLAY,
	LOADING,
	WINSCENE,
	LOSESCENE,
	SETTING,
	UPGRADESCENE,
};

enum class TransitionType
{
	NORMAL,
	FADE,
	CROSSFADE,
};

enum class CollisionType
{
	PLAYER,
	ASTEROID,
	ROCKET
};

class Constant
{
public:
	void SetVisableSize(Size _newSize);
	Size GetVisableSize();
	static Constant* GetInstance();
	~Constant();
private:
	Size visableSize;

protected:
	Constant();
	static Constant * _instance;
};

#endif
