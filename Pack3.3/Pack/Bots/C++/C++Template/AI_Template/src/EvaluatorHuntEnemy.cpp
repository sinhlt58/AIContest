#include "EvaluatorHuntEnemy.h"
#include "Globals.h"

EvaluatorHuntEnemy::~EvaluatorHuntEnemy()
{
}

float EvaluatorHuntEnemy::CalculateDesirability(MyTank* pTank)
{
	if (pTank->GetCoolDown() <= 0)
	{
		return 100;
	}
	return goalHuntEnemy;
}

void EvaluatorHuntEnemy::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalHuntEnemy();
}
