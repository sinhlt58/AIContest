#include "GoalHuntEnemy.h"
#include "GoalType.h"
#include "GoalMoveToPosition.h"

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
	//add subgoal to positon.
	RemoveAllSubgoals();
	AddSubgoal(new GoalMoveToPosition(m_pOwner, m_vCurrentGoodPosition));
}

int GoalHuntEnemy::Process()
{
	//if see enemy then attack.
	ActivateIfInactive();
	m_iStatus = ProcessSubgoals();
	if (m_pOwner->isShootableAEnemy(m_vCurrentAimPosition))
	{
		m_pOwner->FireOn();
		m_pOwner->MoveOff();
		m_pOwner->AimAndShootAtPosition(m_vCurrentAimPosition);
	}
	else
	{
		m_pOwner->FireOff();
		m_pOwner->MoveOn();
	}
	ReactivateIfFailed();
	return m_iStatus;
}

void GoalHuntEnemy::Terminate()
{
}
