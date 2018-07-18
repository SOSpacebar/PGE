#ifndef CONSTANT_H
#define CONSTANT_H

#include "cocos2d.h"
#include "GameStats.h"

using namespace cocos2d;

class GameStats;

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
	void SetHealth(float _health);
	float GetHealth();

	static Constant* GetInstance();
	~Constant();
private:
	Size visableSize;
	GameStats m_stats;
protected:
	Constant();
	static Constant * _instance;
};

#endif
