#include "EvaluatorHuntEnemy.h"

EvaluatorHuntEnemy::~EvaluatorHuntEnemy()
{
}

float EvaluatorHuntEnemy::CalculateDesirability(MyTank* pTank)
{
	if (pTank->GetCoolDown() <= 0)
	{
		return 100;
	}
	return 1;
}

void EvaluatorHuntEnemy::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalHuntEnemy();
}
