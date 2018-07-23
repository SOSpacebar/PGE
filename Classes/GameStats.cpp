#include "GameStats.h"

void GameStats::SetPlayerHealth(float _newHealth)
{
	player.m_health = _newHealth;
}

float GameStats::GetPlayerHealth()
{
	return player.m_health;
}

void GameStats::SetPlayerMaxHealth(float _newHealth)
{
	player.m_maxHealth = _newHealth;
}

float GameStats::GetPlayerMaxHealth()
{
	return player.m_maxHealth;
}

void GameStats::SetPlayerAttackLevel(PlayerAttackLevel _att)
{
	player.m_attack = _att;
}

GameStats::PlayerAttackLevel GameStats::GetPlayerAttackLevel()
{
	return player.m_attack;
}

void GameStats::SetNumOfGameObjects(int _gameObject)
{
	gameObjectCounter = _gameObject;
}

int GameStats::GetNumOfGameObjects()
{
	return gameObjectCounter;
}
