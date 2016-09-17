#include "EvaluatorDodgeStrike.h"

EvaluatorDodgeStrike::~EvaluatorDodgeStrike()
{
}

float EvaluatorDodgeStrike::CalculateDesirability(MyTank* pTank)
{
	return 1;
}

void EvaluatorDodgeStrike::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalDodgeStrike();
}
