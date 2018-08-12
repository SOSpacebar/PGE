#include "WaveSpawner.h"
#include "Asteroid.h"
#include "SceneManager.h"

void WaveSpawner::Init(Node* _spriteNode)
{
	spriteNode = _spriteNode;
	Setup();
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
		else if (state == SpawnState::WAITING)
		{
			if (Constant::GetInstance()->GetGameObjectCount() <= 0)
			{
				if (nextWave > waves.size())
				{
					SceneManager::GetInstance()->RunSceneWithType(SceneType::UPGRADESCENE, TransitionType::FADE);
				}
				else
					nextWave++;
			}
		}
	}
	else
	{
		waveCountDown -= dt;
	}
}

void WaveSpawner::Setup()
{
	delayBetweenWaves = 5.f;
	waveCountDown = delayBetweenWaves;
	state = SpawnState::SETUP;
	spawnCounter = 0;

	int currLevel = Constant::GetInstance()->GetLevel();

	float spawnRate = 1.f - (currLevel * 0.15f);
	int spawnCount = 10 + (currLevel * 2);
	int spawnWaveCount = currLevel + random(1, 3);

	for (size_t i = 0; i < spawnWaveCount; ++i)
	{
		AddWave(spawnCount, spawnRate);
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
