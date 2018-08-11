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
	void SetScore(int _score);
	int GetScore();

	GameStats()
	{
		m_score = 0;
	}

private:
	struct CharaStats
	{
		float m_health;
		float m_maxHealth;
		GameStats::PlayerAttackLevel m_attack = SINGLEROUND;
	} m_player;

	//CharaStats player;
	int m_gameObjectCounter;
	int m_score;
};


#endif // !GAMESTATS_H
