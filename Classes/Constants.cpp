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
