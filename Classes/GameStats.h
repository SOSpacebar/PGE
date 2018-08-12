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

	enum PlayerHealthLevel {
		HEALTHLEVEL1 = 1,
		HEALTHLEVEL2,
		HEALTHLEVEL3_1,
		HEALTHLEVEL3_2
	};

	void SetPlayerHealth(float _newHealth);
	float GetPlayerHealth();
	void SetPlayerMaxHealth(float _newHealth);
	float GetPlayerMaxHealth();
	void SetPlayerRegRate(float _rate);
	float GetPlayerRegRate();

	void SetPlayerAttackLevel(PlayerAttackLevel _att);
	PlayerAttackLevel GetPlayerAttackLevel();
	void SetPlayerHealthLevel(PlayerHealthLevel _hp);
	PlayerHealthLevel GetPlayerHealthLevel();

	void SetNumOfGameObjects(int _gameObject);
	int GetNumOfGameObjects();
	void SetScore(int _score);
	int GetScore();
	void SetLevel(int _level);
	int GetLevel();
	void SetBuildingTF(bool building);
	bool GetBuildingTF();

	GameStats()
	{
		m_score = 0;
		m_level = 0;
		m_building = false;
		m_player.m_health = 0;
		m_player.m_maxHealth = 0;
		m_player.m_regRate = 0;
	}

private:
	struct CharaStats
	{
		float m_health;
		float m_maxHealth;
		float m_regRate;
		GameStats::PlayerAttackLevel m_attack = SINGLEROUND;
		GameStats::PlayerHealthLevel m_healthType = HEALTHLEVEL1;
	} m_player;

	//CharaStats player;
	int m_gameObjectCounter;
	int m_score;
	int m_level;
	bool m_building;

};


#endif // !GAMESTATS_H
