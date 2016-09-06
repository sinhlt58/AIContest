#include "GoalThink.h"
#include "GoalType.h"
#include "GoalMoveToPosition.h"
#include <iostream>
#include "GoalDodgeBullet.h"
#include "EvaluatorDodgeBullet.h"
#include "GoalAtackMainBase.h"
#include "EvaluatorHuntEnemy.h"
#include "GoalHuntEnemy.h"
#include "EvaluatorAttackMainBase.h"
#include "GoalReload.h"
#include "EvaluatorReload.h"


GoalThink::GoalThink(MyTank* pOwner):GoalComposite(pOwner, goal_think)
{
	m_vEvaluators.push_back(new EvaluatorDodgeBullet(1));
	m_vEvaluators.push_back(new EvaluatorHuntEnemy(1));
	m_vEvaluators.push_back(new EvaluatorAttackMainBase(1));
	m_vEvaluators.push_back(new EvaluatorReload(1));
}

GoalThink::~GoalThink()
{
	for (GoalEvaluator* it : m_vEvaluators)
	{
		delete it;
	}
}

void GoalThink::Aribitrate()
{
	GoalEvaluator* bestGoal = nullptr;
	float bestGoalScore = 0;

	for (GoalEvaluator* it : m_vEvaluators)
	{
		float disirability = it->CalculateDesirability(m_pOwner);
		if (disirability > bestGoalScore)
		{
			bestGoal = it;
			bestGoalScore = disirability;
		}
	}

	if (bestGoal)
	{
		bestGoal->SetGoal(m_pOwner);
	}
}

bool GoalThink::notPresent(unsigned goalType) const
{
	if(!m_SubGoals.empty())
	{
		return m_SubGoals.front()->GetType() != goalType;
	}
	return true;
}

void GoalThink::Activate()
{
	m_iStatus = active;
	Aribitrate();
}

int GoalThink::Process()
{
//	ActivateIfInactive();
	m_iStatus = ProcessSubgoals();
//	if (subgoalStatus == completed || subgoalStatus == failed)
//	{
//		m_iStatus = inactive;
//	}
	return m_iStatus;
}

void GoalThink::Terminate()
{
}

void GoalThink::AddGoalHuntEnemy()
{
	RemoveAllSubgoals();
	AddSubgoal(new GoalHuntEnemy(m_pOwner));
}

void GoalThink::AddGoalAttackMainBase()
{
	RemoveAllSubgoals();
	AddSubgoal(new GoalAtackMainBase(m_pOwner));
}

void GoalThink::AddGoalReload()
{
	RemoveAllSubgoals();
	AddSubgoal(new GoalReload(m_pOwner));
}

void GoalThink::AddGoalDodgeBullet()
{
	RemoveAllSubgoals();
	AddSubgoal(new GoalDodgeBullet(m_pOwner));
//	AddSubgoal(new GoalReload(m_pOwner));
}
