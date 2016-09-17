#include "EvaluatorGetPowerUp.h"
#include "MyTeam.h"
#include "HelperFunctions.h"

EvaluatorGetPowerUp::~EvaluatorGetPowerUp()
{
}

float EvaluatorGetPowerUp::CalculateDesirability(MyTank* pTank)
{
	if (MyTeamMgr->GetClosetTankToPowerUpId() == pTank->ID())
	{
		return 101;
	}
	return 1;
}

void EvaluatorGetPowerUp::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalGetPowerUp();
}
