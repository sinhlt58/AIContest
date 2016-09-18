#include "MyTeam.h"
#include <ai/PowerUp.h>
#include <ai/AI.h>
#include "Globals.h"
#include "HelperFunctions.h"

int const left_side = 7;
int const right_side = 14;
int const prepare_time = 3;

MyTeam::MyTeam()
{
	float preparingX;
	m_iClosestTankToPowerUp = -1;
	if (AI::GetInstance()->GetMyTeam() == TEAM_1)
	{
		m_fEnemySide = right_side;
		m_fMySide = left_side;
		m_iMyTeam = TEAM_1;
		m_iEnemyTeam = TEAM_2;
		preparingX = 9;
	}else
	{
		m_fEnemySide = left_side;
		m_fMySide = right_side;
		m_iMyTeam = TEAM_2;
		m_iEnemyTeam = TEAM_1;
		preparingX = 12;
	}
	for (int i=1; i<=MAP_W-2;i++)
	{
		m_vPreparingPositions.push_back(glm::vec2(preparingX, i));
	}
	m_iCurrentState = PREPARE_ATTACKING;
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
	UpdateTarget();
	UpdateState();
	for (MyTank* tank : m_vTanks)
	{
		tank->Update();
	}
	Globals::s_TotalLoops++;
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

void MyTeam::UpdateTarget()
{
	for (MyTank* tank : m_vTanks)
	{
		if (tank->GetApiTank()->GetHP() > 0)
		{
			TargetMgr->UpdateTargetForATank(tank);
		}
	}
}

void MyTeam::UpdateState()
{
	if (Globals::s_TotalLoops <= prepare_time)
	{
		m_iCurrentState = PREPARE_ATTACKING;
	}	
	else
	{
		m_iCurrentState = ATTACKING;
	}
}

void MyTeam::SetState(unsigned state)
{
	m_iCurrentState = state;
}

unsigned MyTeam::GetCurrentState()
{
	return m_iCurrentState;
}

bool MyTeam::isMyTankInsideMySide(glm::vec2 tankPos)
{
	return isTankInsideTheirSide(tankPos.x, 
		m_iMyTeam, m_fMySide);
}

bool MyTeam::isEnemyTankInsideTheirSide(glm::vec2 tankPos)
{
	return isTankInsideTheirSide(tankPos.x,
		m_iEnemyTeam, m_fEnemySide);
}

bool MyTeam::isTankInsideTheirSide(float x, int team, float sideX)
{
	if (team == TEAM_1)
	{
		return x < sideX + 1;
	}
	else if (team == TEAM_2)
	{
		return x > sideX - 1;
	}
	return false;
}

glm::vec2 MyTeam::GetBestPreparingPosition(glm::vec2 tankPos)
{
	float closestDistance = 999;
	glm::vec2 bestPreparingPos;
	for (glm::vec2 p : m_vPreparingPositions)
	{
		float distance = Manhattan(p, tankPos);
		if (distance < closestDistance)
		{
			closestDistance = distance;
			bestPreparingPos = p;
		}
	}
	return bestPreparingPos;
}

MyTeam* MyTeam::GetInstance()
{
	static MyTeam instance = MyTeam();
	return &instance;
}
