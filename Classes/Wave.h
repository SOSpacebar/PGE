#ifndef WAVE_H
#define WAVE_H

#include "GameObject.h"

class Wave
{
public:
	Wave(int _num, float _rate);
	~Wave();
	int count;
	float rate;
private:
};
#endif // !WAVE_H
