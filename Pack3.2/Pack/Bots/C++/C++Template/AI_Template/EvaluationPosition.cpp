#include "EvaluationPosition.h"
#include "Globals.h"

EvaluationPosition::~EvaluationPosition()
{
}

void EvaluationPosition::EvaluateNumLineOfFireScore(float weight)
{
	for (glm::vec2 p : TargetMgr->GetAllAliveEnemyPositions())
	{
		if (TargetMgr->isShootableAEnemy(m_vPosition, p))
			m_fScore += weight;
	}
}

void EvaluationPosition::EvaluateRangeAttackForSniperScore(glm::vec2 enemyPosition, float weight)
{
	m_fScore += int(Manhattan(enemyPosition, m_vPosition))%BEST_RANGE_SNIPER*weight;
}

bool EvaluationPosition::operator<(const EvaluationPosition& right) const
{
	return GetScore() < right.GetScore();
}

/*Functions for pick best enemy target*/
void EvaluationPosition::EvaluateDistanceToMyTankScore(MyTank* myTank, float weight)
{
	m_fScore += 1/(Manhattan(myTank->GetPosition(), m_vPosition)*weight + 1);
}

void EvaluationPosition::EvaluateDistanceToItemsScore(float weight)
{
	//still thinking...
	m_fScore += 0;
}

void EvaluationPosition::EvaluateNumberOfMyTankChosenScore(int enemyId, float weight)
{
	m_fScore += TargetMgr->GetNumChosen(enemyId)*weight;
}
