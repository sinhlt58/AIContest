#include "GoalThink.h"
#include "GoalType.h"
#include "GoalMoveToPosition.h"
#include <iostream>


GoalThink::GoalThink(MyTank* pOwner):GoalComposite(pOwner, goal_think)
{
}

GoalThink::~GoalThink()
{
}


void GoalThink::Aribitrate()
{
	AddSubgoal(new GoalMoveToPosition(m_pOwner, (*m_pOwner).m_vTmpTarget));
}

bool GoalThink::notPresent(unsigned goalType) const
{
	return false;
}

void GoalThink::Activate()
{
	m_iStatus = active;
	Aribitrate();
}

int GoalThink::Process()
{
	ActivateIfInactive();
	int subgoalStatus = ProcessSubgoals();
	if (subgoalStatus == completed || subgoalStatus == failed)
	{
		m_iStatus = inactive;
	}
	return m_iStatus;
}

void GoalThink::Terminate()
{
}
