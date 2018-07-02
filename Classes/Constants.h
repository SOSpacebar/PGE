#ifndef CONSTANT_H
#define CONSTANT_H

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

#endif
