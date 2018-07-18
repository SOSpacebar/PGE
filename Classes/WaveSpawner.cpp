#include "WaveSpawner.h"
#include "Asteroid.h"

void WaveSpawner::Init(Node* _spriteNode)
{
	delayBetweenWaves = 5.f;
	waveCountDown = delayBetweenWaves;
	state = SpawnState::COUNTING;
	spawnCounter = 0;
	spriteNode = _spriteNode;
}

void WaveSpawner::Update(float dt)
{
	if (waveCountDown < 0)
	{
		if (state != SpawnState::WAITING)
		{
			SpawnWave(waves[nextWave]);
			waveCountDown = waves[nextWave].rate;
		}
	}
	else
	{
		waveCountDown -= dt;
	}
}

void WaveSpawner::SpawnWave(Wave &_wave)
{
	state = SpawnState::SPAWNING;

	if (spawnCounter < _wave.count)
	{
		SpawnAsteroid();
		++spawnCounter;
	}
	else
	{
		state = SpawnState::WAITING;
	}
}

void WaveSpawner::SpawnAsteroid()
{
	GameAsteroid* asteroids = new GameAsteroid();
	float asteroidRandX = random(0, (int)(Constant::GetInstance()->GetVisableSize().width - 10));
	asteroids->Init("Asteroid.png", "Asteroids", asteroidRandX, (Constant::GetInstance()->GetVisableSize().height - 10), 0);
	spriteNode->addChild(asteroids);
}

void WaveSpawner::AddWave(int _number, float _rate)
{
	Wave newWave(_number, _rate);
	waves.push_back(newWave);
}
