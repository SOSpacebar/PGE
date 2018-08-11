#include "GameStats.h"

void GameStats::SetPlayerHealth(float _newHealth)
{
	m_player.m_health = _newHealth;
}

float GameStats::GetPlayerHealth()
{
	return m_player.m_health;
}

void GameStats::SetPlayerMaxHealth(float _newHealth)
{
	m_player.m_maxHealth = _newHealth;
}

float GameStats::GetPlayerMaxHealth()
{
	return m_player.m_maxHealth;
}

void GameStats::SetPlayerAttackLevel(PlayerAttackLevel _att)
{
	m_player.m_attack = _att;
}

GameStats::PlayerAttackLevel GameStats::GetPlayerAttackLevel()
{
	return m_player.m_attack;
}

void GameStats::SetNumOfGameObjects(int _gameObject)
{
	m_gameObjectCounter = _gameObject;
}

int GameStats::GetNumOfGameObjects()
{
	return m_gameObjectCounter;
}

void GameStats::SetScore(int _score)
{
	m_score = _score;
}

int GameStats::GetScore()
{
	return m_score;
}
