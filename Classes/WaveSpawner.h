#ifndef WAVE_SPAWNER_H
#define WAVE_SPAWNER_H

#include "Wave.h"
#include "Constants.h"

using namespace cocos2d;

class WaveSpawner
{
public:
	enum SpawnState {
		SETUP,
		SPAWNING,
		WAITING,
	};

	void Init(Node * _spriteNode);
	void Update(float dt);
	void Setup();
	void SpawnWave(Wave &_wave);
	void SpawnAsteroid();

	void AddWave(int _number, float _rate);

	std::vector<Wave> waves;

	float delayBetweenWaves;
	float waveCountDown;
	int spawnCounter;

	SpawnState state;
private:
	int nextWave;

	Node* spriteNode;

};




#endif // !WAVE_SPAWNER_H
