#ifndef CONSTANT_H
#define CONSTANT_H

enum class SceneType
{
	NONE,
	MAINMENU,
	GAMEPLAY,
	LOADING,
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
