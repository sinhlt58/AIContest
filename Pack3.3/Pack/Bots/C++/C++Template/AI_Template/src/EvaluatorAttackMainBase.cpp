#include "EvaluatorAttackMainBase.h"

EvaluatorAttackMainBase::~EvaluatorAttackMainBase()
{
}

float EvaluatorAttackMainBase::CalculateDesirability(MyTank* pTank)
{
	return 10;
}

void EvaluatorAttackMainBase::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalAttackMainBase();
}
