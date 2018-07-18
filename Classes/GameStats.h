#ifndef GAMESTATS_H
#define GAMESTATS_H

class GameStats
{
public:
	void SetPlayerHealth(float _newHealth);
	float GetPlayerHealth();
	void SetNumOfGameObjects(int _gameObject);
	int GetNumOfGameObjects();
private:
	float playerHealth;
	int gameObjectCounter;
};


#endif // !GAMESTATS_H
