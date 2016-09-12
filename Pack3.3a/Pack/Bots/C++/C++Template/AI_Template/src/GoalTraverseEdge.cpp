#include "GoalTraverseEdge.h"
#include "GoalType.h"
#include "HelperFunctions.h"
#include "Globals.h"

GoalTraverseEdge::GoalTraverseEdge(MyTank* pOwner, PathEdge edge, bool lastEdge):
	Goal<MyTank>(pOwner, goal_traverse_edge),
	m_Edge(edge),
	m_bLastEdgeInPath(lastEdge),
	m_dTimeExpected(0)
{
}

bool GoalTraverseEdge::isStuck() const
{
	return false;
}


void GoalTraverseEdge::Activate()
{
	m_iStatus = active;
	m_pOwner->GetSteering()->SetTarget(m_Edge.Destination());
	m_pOwner->GetSteering()->SeekOn();
	m_pOwner->MoveOn();
	int nextDirToMove = m_pOwner->GetSteering()->Calculate();

	if (nextDirToMove != DIRECTION_NONE)
	{
		glm::vec2 nextPosInTheFuture = m_pOwner->GetPosition() + 
			m_pOwner->GetSpeed() * GetDirByDefineDir(nextDirToMove);
		Bullet* closestBullet = TargetMgr->GetClosestDangerBullet(nextPosInTheFuture);
		if (closestBullet)
		{
			m_pOwner->GetSteering()->SeekOff();
			m_pOwner->MoveOff();
		}else
		{
			m_pOwner->GetSteering()->SeekOn();
			m_pOwner->MoveOn();
		}
	}else
	{
		m_pOwner->GetSteering()->SeekOff();
		m_pOwner->MoveOff();
	}
}

int GoalTraverseEdge::Process()
{
	ActivateIfInactive();

	if (isStuck())
	{
		m_iStatus = failed;
	}
	
	if(m_pOwner->isAtPosition(m_Edge.Destination()))
	{
		m_iStatus = completed;	
	}
	return m_iStatus;
}

void GoalTraverseEdge::Terminate()
{
	m_pOwner->GetSteering()->SeekOff();
	m_pOwner->MoveOff();
}
