#include "MyTeam.h"
#include <ai/PowerUp.h>
#include <ai/AI.h>
#include "Globals.h"
#include "HelperFunctions.h"

MyTeam::MyTeam()
{
	m_iClosestTankToPowerUp = -1;
}

MyTeam::~MyTeam()
{
}

void MyTeam::SetTanks(std::vector<MyTank*> tanks)
{
	m_vTanks = tanks;
	
}

void MyTeam::Update()
{
	UpdateClosestTankToPowerUp();
	PrintVector("Power pos: ", m_vCurrentPowerUpPos);
	for (MyTank* tank : m_vTanks)
	{
		tank->Update();
	}
}

void MyTeam::UpdateClosestTankToPowerUp()
{
	std::vector<PowerUp*>  powerUp = AI::GetInstance()->GetPowerUpList();
	m_iClosestTankToPowerUp = -1;
	m_vCurrentPowerUpPos = glm::vec2();
	if (!powerUp.empty())
	{
		m_vCurrentPowerUpPos = glm::vec2(powerUp[0]->GetX(), powerUp[0]->GetY());
		float fastestTimeToPowerUp = 999;
		for (MyTank* tank : m_vTanks)
		{
			if (tank->GetApiTank()->GetHP() > 0)
			{
				float distance = Manhattan(m_vCurrentPowerUpPos, tank->GetPosition());
				int timeToGetPowerUp = distance / tank->GetSpeed();
				if (timeToGetPowerUp < fastestTimeToPowerUp)
				{
					fastestTimeToPowerUp = timeToGetPowerUp;
					m_iClosestTankToPowerUp = tank->ID();
				}
			}		
		}
	}
}

MyTeam* MyTeam::GetInstance()
{
	static MyTeam instance = MyTeam();
	return &instance;
}
