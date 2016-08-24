#include "TargetingSystem.h"
#include "include/ai/AI.h"
#include "AStarAlgorithm.h"

TargetingSystem::~TargetingSystem()
{
}

TargetingSystem::TargetingSystem(MyTank* pOwner):m_pOwner(pOwner),
												 m_iTargetEnemyId(-1)
{
	
}

void TargetingSystem::Update()
{
	//find enemy target.
	float closestManhatan = 99;
	float closestManhatanAndShootable = 99;
	for (int i = 0; i<NUMBER_OF_TANK; i++)
	{
		if (m_pOwner->GetVisionSystem()->isEnemyAlive(i))
		{
			glm::vec2 enemyPosition = m_pOwner->GetVisionSystem()->GetEnemyPosition(i);
			float distanceToEnemy = AStarAlgorithm::Manhattan(m_pOwner->GetPosition(), enemyPosition);
			if (distanceToEnemy < closestManhatan)
			{
				closestManhatan = distanceToEnemy;
				m_iTargetEnemyId = i;
			}
//			if (m_pOwner->GetVisionSystem()->isEnemyShootable(i) && distanceToEnemy < closestManhatanAndShootable)
//			{
//				closestManhatanAndShootable = distanceToEnemy;
//				m_iTargetEnemyId = i;
//			}
		}
	}
}

bool TargetingSystem::isTargetingEnemyPresent()
{
	return m_iTargetEnemyId != -1;
}

bool TargetingSystem::isTargetingEnemyShootable()
{
	return m_pOwner->GetVisionSystem()->isEnemyShootable(m_iTargetEnemyId);
}

glm::vec2 TargetingSystem::GetTargetingEnemyPosition()
{
	return m_pOwner->GetVisionSystem()->GetEnemyPosition(m_iTargetEnemyId);
}

int TargetingSystem::GetAimDirection()
{
	int roundMyTankX = round(m_pOwner->GetPosition().x);
	int roundMyTankY = round(m_pOwner->GetPosition().y);
	int roundTargetTankX = round(GetTargetingEnemyPosition().x);
	int roundTargetTankY = round(GetTargetingEnemyPosition().y);

	if (roundMyTankX == roundTargetTankX)
	{
		if (roundTargetTankY > roundMyTankY)
			return DIRECTION_DOWN;
		return DIRECTION_UP;
	}

	if (roundMyTankY == roundTargetTankY)
	{
		if (roundTargetTankX > roundMyTankX)
			return DIRECTION_RIGHT;
		return DIRECTION_LEFT;
	}

	return DIRECTION_NONE;
}
