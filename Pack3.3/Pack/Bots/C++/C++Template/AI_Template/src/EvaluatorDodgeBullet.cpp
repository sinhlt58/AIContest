#include "EvaluatorDodgeBullet.h"

EvaluatorDodgeBullet::~EvaluatorDodgeBullet()
{
}


float EvaluatorDodgeBullet::CalculateDesirability(MyTank* pTank)
{
//	if (pTank->GetCoolDown() > 0)
//	{
//		return 100;
//	}
	return 1;
}

void EvaluatorDodgeBullet::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalDodgeBullet();
}
