#include "GoalAtackMainBase.h"
#include "GoalMoveToPosition.h"

GoalAtackMainBase::~GoalAtackMainBase()
{
}


void GoalAtackMainBase::Activate()
{
	m_iStatus = active;
	RemoveAllSubgoals();
	m_vAimTarget = TargetMgr->GetEnemyMainBasePositions()[m_pOwner->ID()];
	m_vGoodPosition = m_vAimTarget - glm::vec2(0, 3);
	AddSubgoal(new GoalMoveToPosition(m_pOwner, m_vGoodPosition));
}

int GoalAtackMainBase::Process()
{
	ActivateIfInactive();
	m_iStatus = ProcessSubgoals();
	if(m_pOwner->isShootableBase(m_vAimTarget))
	{
		m_pOwner->FireOn();
		m_pOwner->MoveOff();
		m_pOwner->AimAndShootAtPosition(m_vAimTarget);
	}else
	{
		m_pOwner->FireOff();
		m_pOwner->MoveOn();
	}
	ReactivateIfFailed();
	return m_iStatus;
}

void GoalAtackMainBase::Terminate()
{
//	m_pOwner->FireOff();
}
