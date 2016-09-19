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
//		PrintVector("Tank to powerup: ", pTank->GetPosition());
		return 1;
	}
	return 1;
}

void EvaluatorGetPowerUp::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalGetPowerUp();
}
