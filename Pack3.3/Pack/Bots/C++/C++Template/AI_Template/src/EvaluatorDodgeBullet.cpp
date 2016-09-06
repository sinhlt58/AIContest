#include "EvaluatorDodgeBullet.h"
#include "Globals.h"

EvaluatorDodgeBullet::~EvaluatorDodgeBullet()
{
}


float EvaluatorDodgeBullet::CalculateDesirability(MyTank* pTank)
{
	if (AI::GetInstance()->GetMyTeam() == TEAM_2)
		return 0;

	Bullet* closestBullet = TargetMgr->GetClosestDangerBullet(pTank->GetPosition());
	if (closestBullet)
	{
		if (TargetMgr->isBulletDangerous(pTank, closestBullet))
		{
			pTank->SetCurrentClosestDangerBullet(closestBullet);
			return 1;
		}
	}
	return goalDodgeBullet;
}

void EvaluatorDodgeBullet::SetGoal(MyTank* pTank)
{
	pTank->GetBrain()->AddGoalDodgeBullet();
}
