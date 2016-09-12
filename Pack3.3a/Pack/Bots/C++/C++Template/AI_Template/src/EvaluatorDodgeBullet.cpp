#include "EvaluatorDodgeBullet.h"
#include "Globals.h"
#include "HelperFunctions.h"

EvaluatorDodgeBullet::~EvaluatorDodgeBullet()
{
}


float EvaluatorDodgeBullet::CalculateDesirability(MyTank* pTank)
{
	Bullet* closestBullet = TargetMgr->GetClosestDangerBullet(pTank->GetPosition());
	if (closestBullet)
	{
		if (TargetMgr->isTheClosestBulletDangerous(pTank, closestBullet))
		{
			return 1000;
		}	
	}
	return 0;
}

void EvaluatorDodgeBullet::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalDodgeBullet();
}
