#include "GoalDodgeBullet.h"
#include "GoalType.h"
#include "GoalMoveToPosition.h"

GoalDodgeBullet::~GoalDodgeBullet()
{
}


GoalDodgeBullet::GoalDodgeBullet(MyTank* pOwner):GoalComposite(pOwner, goal_dodge_bullet)
{
}

void GoalDodgeBullet::Activate()
{
	m_iStatus = active;
	glm::vec2 safePosition = TargetMgr->GetBestPositionForSniperToReaload(m_pOwner);
	RemoveAllSubgoals();
	m_pOwner->MoveOn();
	AddSubgoal(new GoalMoveToPosition(m_pOwner, safePosition));
}

int GoalDodgeBullet::Process()
{
	ActivateIfInactive();
	m_iStatus = ProcessSubgoals();
	ReactivateIfFailed();
	return m_iStatus;
}

void GoalDodgeBullet::Terminate()
{
}
