#include "Constants.h"

// Singleton
Constant * Constant::_instance = NULL;

void Constant::SetVisableSize(Size _newSize)
{
	visableSize = _newSize;
}

Size Constant::GetVisableSize()
{
	return visableSize;
}

void Constant::SetGameObjectCount(int _num)
{
	m_stats.SetNumOfGameObjects(_num);
}

int Constant::GetGameObjectCount()
{
	return m_stats.GetNumOfGameObjects();
}

void Constant::SetHealth(float _health)
{
	m_stats.SetPlayerHealth(_health);
}

float Constant::GetHealth()
{
	return m_stats.GetPlayerHealth();
}

void Constant::SetMaxHealth(float _mhealth)
{
	m_stats.SetPlayerMaxHealth(_mhealth);
}

float Constant::GetMaxHealth()
{
	return m_stats.GetPlayerMaxHealth();
}

void Constant::SetAttackLevel(GameStats::PlayerAttackLevel _lvl)
{
	m_stats.SetPlayerAttackLevel(_lvl);
}

GameStats::PlayerAttackLevel Constant::GetAttackLevel()
{
	return m_stats.GetPlayerAttackLevel();
}

Constant * Constant::GetInstance()
{
	if (!_instance)
		_instance = new Constant();
	return _instance;
}

Constant::~Constant()
{
	if (_instance)
	{
		delete _instance;
		_instance = 0;
	}
}

Constant::Constant()
{
}
