#pragma once
#include "MyTank.h"

#define MyTeamMgr MyTeam::GetInstance()

class MyTank;
enum
{
	DEFENDING,
	ATTACKING,
	PREPARE_ATTACKING
};
class  MyTeam
{
public:
	MyTeam();
	~MyTeam();
	void SetTanks(std::vector<MyTank*> tanks);
	void Update();
	
	/*Get PowerUp functions*/
	void UpdateClosestTankToPowerUp();
	int GetClosetTankToPowerUpId() { return m_iClosestTankToPowerUp; }
	glm::vec2 GetCurrentPowerUpPos() { return m_vCurrentPowerUpPos; }

	/*Update target for each tank*/
	void UpdateTarget();
	
	/*State*/
	void UpdateState();
	void SetState(unsigned int state);
	unsigned int GetCurrentState();
	bool isMyTankInsideMySide(glm::vec2 tankPos);
	bool isEnemyTankInsideTheirSide(glm::vec2 tankPos);
	bool isTankInsideTheirSide(float y, int team, float sideY);

	/*Preparing for attacking*/
	glm::vec2 GetBestPreparingPosition(glm::vec2 tankPos);

	static MyTeam* GetInstance();
private:
	std::vector<MyTank*> m_vTanks;
	int m_iClosestTankToPowerUp;
	glm::vec2 m_vCurrentPowerUpPos;
	unsigned int m_iCurrentState;
	float m_fEnemySide;
	float m_fMySide;
	int m_iMyTeam;
	int m_iEnemyTeam;
	std::vector<glm::vec2> m_vPreparingPositions;
	std::vector<glm::vec2> m_vDefendingPositions;
};