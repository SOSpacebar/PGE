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
	void SetGameObjectCount(int _num);
	int GetGameObjectCount();
	
	// Player Stuff
	void SetHealth(float _health);
	float GetHealth();
	void SetMaxHealth(float _mhealth);
	float GetMaxHealth();
	void SetAttackLevel(GameStats::PlayerAttackLevel _lvl);
	GameStats::PlayerAttackLevel GetAttackLevel();

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
