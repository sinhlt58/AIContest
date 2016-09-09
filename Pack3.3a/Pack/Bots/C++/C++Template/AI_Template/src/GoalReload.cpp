#include "GoalReload.h"
#include "GoalType.h"
#include "GoalMoveToPosition.h"
#include "HelperFunctions.h"

GoalReload::GoalReload(MyTank* pOwner):GoalComposite(pOwner, goal_reload)
{

}

GoalReload::~GoalReload()
{
}

void GoalReload::Activate()
{
	m_iStatus = active;
	glm::vec2 safePosition = TargetMgr->GetBestPositionForSniperToReaload(m_pOwner);
	RemoveAllSubgoals();
	m_pOwner->MoveOn();
	if (!m_pOwner->isSafe())
	{
		AddSubgoal(new GoalMoveToPosition(m_pOwner, safePosition));
//		PrintVector("Tank pos: ", m_pOwner->GetPosition());
//		PrintVector("Safe pos: ", safePosition);
	}	
	else
	{
//		PrintVector("Tank pos: ", m_pOwner->GetPosition());
//		std::cout << "FUCK\n";
		m_pOwner->MoveOff();
	}
}

int GoalReload::Process()
{
	ActivateIfInactive();
	m_iStatus = ProcessSubgoals();
	ReactivateIfFailed();
	return m_iStatus;
}

void GoalReload::Terminate()
{
	m_pOwner->MoveOn();
}
