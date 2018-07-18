#ifndef GAMESTATS_H
#define GAMESTATS_H

class GameStats
{
public:
	void SetPlayerHealth(float _newHealth);
	float GetPlayerHealth();
	
private:
	float playerHealth;
};


#endif // !GAMESTATS_H
