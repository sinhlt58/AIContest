#pragma once
#include "MyTank.h"

#define MyTeamMgr MyTeam::GetInstance()

class MyTank;

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

	static MyTeam* GetInstance();
private:
	std::vector<MyTank*> m_vTanks;
	int m_iClosestTankToPowerUp;
	glm::vec2 m_vCurrentPowerUpPos;
};