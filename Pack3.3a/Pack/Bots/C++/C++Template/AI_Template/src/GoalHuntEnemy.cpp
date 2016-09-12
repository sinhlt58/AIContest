#include "GoalHuntEnemy.h"
#include "GoalType.h"
#include "GoalMoveToPosition.h"
#include "GoalShootEnemy.h"
#include "GoalReload.h"
#include "Globals.h"
#include "HelperFunctions.h"

GoalHuntEnemy::~GoalHuntEnemy()
{
}

GoalHuntEnemy::GoalHuntEnemy(MyTank* pOwner):GoalComposite(pOwner, goal_hunt_enemy)
{
}

void GoalHuntEnemy::Activate()
{
	m_iStatus = active;
	//chose best enemy target.
	m_vCurrentAimPosition = TargetMgr->GetBestEnemyTargetPositionToAttack(m_pOwner);
	//chose best position to go.
	m_vCurrentGoodPosition = TargetMgr->GetBestPositionForSniperToAttack(m_pOwner, m_vCurrentAimPosition);
//	PrintVector("Mytank position: ", m_pOwner->GetPosition());
//	PrintVector("Target position: ", m_vCurrentAimPosition);
//	PrintVector("Position to attack: ", m_vCurrentGoodPosition);
	//add subgoal to positon.
	RemoveAllSubgoals();
	//not shoot when too far or cooldown of enemy is zero (assume enemy will attack soo :D.)
//	if (m_pOwner->isSafe())
//	{
		if (m_pOwner->isShootableAEnemy(m_vCurrentAimPosition))
		{
			if (m_pOwner->isCurrentEnemyTargetPresent())
			{	
				Tank* enemTank = AI::GetInstance()->GetEnemyTank(m_pOwner->GetCurrentEnemyId());
				int typeEnemy = enemTank->GetType();
				AddSubgoal(new GoalShootEnemy(m_pOwner, m_vCurrentAimPosition));
			}
		}
		else
		{
//			m_pOwner->MoveOn();
			AddSubgoal(new GoalMoveToPosition(m_pOwner, m_vCurrentGoodPosition));
		}
//	}else
//	{
//		AddSubgoal(new GoalReload(m_pOwner));
//	}
		
	
}

int GoalHuntEnemy::Process()
{
	//if see enemy then attack.
	ActivateIfInactive();
	m_iStatus = ProcessSubgoals();
	ReactivateIfFailed();
	return m_iStatus;
}

void GoalHuntEnemy::Terminate()
{
//	m_pOwner->MoveOff();
}
