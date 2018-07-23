#ifndef GAMESTATS_H
#define GAMESTATS_H



class GameStats
{
public:
	enum PlayerAttackLevel {
		SINGLEROUND,
		DOUBLEROUND,
		TRIPLEROUND,
		SPLITROUND
	};

	void SetPlayerHealth(float _newHealth);
	float GetPlayerHealth();
	void SetPlayerMaxHealth(float _newHealth);
	float GetPlayerMaxHealth();
	void SetPlayerAttackLevel(PlayerAttackLevel _att);
	PlayerAttackLevel GetPlayerAttackLevel();
	void SetNumOfGameObjects(int _gameObject);
	int GetNumOfGameObjects();

private:
	struct CharaStats
	{
		float m_health;
		float m_maxHealth;
		GameStats::PlayerAttackLevel m_attack = SINGLEROUND;
	} player;

	//CharaStats player;
	int gameObjectCounter;
};


#endif // !GAMESTATS_H
