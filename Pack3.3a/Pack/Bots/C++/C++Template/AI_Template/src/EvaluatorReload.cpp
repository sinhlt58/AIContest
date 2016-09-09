#include "EvaluatorReload.h"

EvaluatorReload::~EvaluatorReload()
{
}

float EvaluatorReload::CalculateDesirability(MyTank* pTank)
{
	if (pTank->GetCoolDown() >= 0)
		return 1;
	return 1;
}

void EvaluatorReload::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalReload();
}
