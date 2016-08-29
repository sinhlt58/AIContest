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
	std::cout << "Tank Position: " << m_pOwner->GetPosition().x << " " << m_pOwner->GetPosition().y << std::endl;
	std::cout << "Safe position: " << safePosition.x << " " << safePosition.y << std::endl;
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
