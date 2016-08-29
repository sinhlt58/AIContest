#include "GoalMoveToPosition.h"
#include "GoalType.h"
#include "GoalFollowPath.h"
#include <iostream>

GoalMoveToPosition::GoalMoveToPosition(MyTank* pOwner, glm::vec2 d):
	GoalComposite(pOwner, goal_move_to_position),
	m_vDestination(d)
{
}

void GoalMoveToPosition::Activate()
{
	m_iStatus = active;
	RemoveAllSubgoals();
	if(m_pOwner->GetPathPlanner()->RequestPathToPosition(m_vDestination))
	{
		AddSubgoal(new GoalFollowPath(m_pOwner, m_pOwner->GetPathPlanner()->GetPathAsEdges()));
	}else
	{
		std::cout << "Cant find a path.\n";
	}
}

int GoalMoveToPosition::Process()
{
	ActivateIfInactive();
	m_iStatus = ProcessSubgoals();
	if(m_iStatus == completed)
	{
		std::cout << "Completed";
	}

	ReactivateIfFailed();

	return m_iStatus;
}

void GoalMoveToPosition::Terminate()
{
}
