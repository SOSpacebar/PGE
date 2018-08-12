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

void GameStats::SetPlayerRegRate(float _rate)
{
	m_player.m_regRate = _rate;
}

float GameStats::GetPlayerRegRate()
{
	return m_player.m_regRate;
}

void GameStats::SetPlayerAttackLevel(PlayerAttackLevel _att)
{
	m_player.m_attack = _att;
}

GameStats::PlayerAttackLevel GameStats::GetPlayerAttackLevel()
{
	return m_player.m_attack;
}

void GameStats::SetPlayerHealthLevel(PlayerHealthLevel _hp)
{
	m_player.m_healthType = _hp;
}

GameStats::PlayerHealthLevel GameStats::GetPlayerHealthLevel()
{
	return m_player.m_healthType;
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

void GameStats::SetLevel(int _level)
{
	m_level = _level;
}

int GameStats::GetLevel()
{
	return m_level;
}

void GameStats::SetBuilding(int building)
{
	m_building = building;
}

int GameStats::GetBuilding()
{
	return m_building;
}
