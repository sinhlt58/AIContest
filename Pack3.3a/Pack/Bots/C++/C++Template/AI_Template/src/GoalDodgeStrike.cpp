#include "GoalDodgeStrike.h"
#include "GoalType.h"

GoalDodgeStrike::GoalDodgeStrike(MyTank* pOwner):
	GoalComposite<MyTank>(pOwner, goal_dodge_strike)
{
}

GoalDodgeStrike::~GoalDodgeStrike()
{
}

void GoalDodgeStrike::Activate()
{
	m_iStatus = active;
}

int GoalDodgeStrike::Process()
{
	ActivateIfInactive();
	m_iStatus = ProcessSubgoals();
	m_pOwner->StopInTheNextStepIsDangerous();
	ReactivateIfFailed();
	return m_iStatus;
}

void GoalDodgeStrike::Terminate()
{
}
