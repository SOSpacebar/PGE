#include "GameStats.h"

void GameStats::SetPlayerHealth(float _newHealth)
{
	playerHealth = _newHealth;
}

float GameStats::GetPlayerHealth()
{
	return playerHealth;
}

void GameStats::SetNumOfGameObjects(int _gameObject)
{
	gameObjectCounter = _gameObject;
}

int GameStats::GetNumOfGameObjects()
{
	return gameObjectCounter;
}
