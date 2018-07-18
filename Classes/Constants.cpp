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

void Constant::SetHealth(float _health)
{
	m_stats.SetPlayerHealth(_health);
}

float Constant::GetHealth()
{
	return m_stats.GetPlayerHealth();
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
