#include "GoalReload.h"
#include "GoalType.h"
#include "GoalMoveToPosition.h"
#include "HelperFunctions.h"
#include "GoalCover.h"

GoalReload::GoalReload(MyTank* pOwner):GoalComposite(pOwner, goal_reload)
{

}

GoalReload::~GoalReload()
{
}

void GoalReload::Activate()
{
	m_iStatus = active;
	RemoveAllSubgoals();
	std::vector<glm::vec2> enemyPos = TargetMgr->GetAllAliveEnemyPositions();
	AddSubgoal(new GoalCover(m_pOwner, enemyPos));
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

}
