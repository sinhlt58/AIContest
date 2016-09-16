#include "GoalHuntEnemy.h"
#include "GoalType.h"
#include "GoalMoveToPosition.h"
#include "GoalShootEnemy.h"
#include "GoalReload.h"
#include "Globals.h"
#include "HelperFunctions.h"
#include "GoalGoToPosToAttackEnemy.h"
#include "GoalCover.h"

GoalHuntEnemy::~GoalHuntEnemy()
{
}

GoalHuntEnemy::GoalHuntEnemy(MyTank* pOwner):GoalComposite(pOwner, goal_hunt_enemy)
{
}

void GoalHuntEnemy::Activate()
{
//	std::cout << "Inside goal huntn enemy.\n";
	m_iStatus = active;
	//chose best enemy target.
	m_vCurrentAimPosition = TargetMgr->GetBestEnemyTargetPositionToAttack(m_pOwner);
	//chose best position to go.
//	m_vCurrentGoodPosition = TargetMgr->GetBestPositionForSniperToAttack(m_pOwner, m_vCurrentAimPosition);
//	PrintVector("Mytank position: ", m_pOwner->GetPosition());
//	PrintVector("Target position: ", m_vCurrentAimPosition);
//	PrintVector("Position to attack: ", m_vCurrentGoodPosition);
	//add subgoal to positon.
	RemoveAllSubgoals();
	//not shoot when too far or cooldown of enemy is zero (assume enemy will attack soo :D.)
	if (m_pOwner->isShootableAEnemy(m_vCurrentAimPosition))
	{
		if (m_pOwner->isCurrentEnemyTargetPresent())
		{	
//			Tank* enemyTank = AI::GetInstance()->GetEnemyTank(m_pOwner->GetCurrentEnemyId());
//			int typeEnemy = enemyTank->GetType();
//			int enemyCoolDown = enemyTank->GetCoolDown();
//			glm::vec2 enemyPos = glm::vec2(enemyTank->GetX(), enemyTank->GetY());
//			glm::vec2 dirToMyTank = TargetMgr->GetDirInViewPointToPoint(m_pOwner->GetPosition(), enemyPos);
//			if (enemyCoolDown > 0)
//			{
//				AddSubgoal(new GoalShootEnemy(m_pOwner, m_vCurrentAimPosition));
//			}else
//			{
//				if (m_pOwner->GetApiTank()->GetType() == TANK_HEAVY)
//				{
//					AddSubgoal(new GoalShootEnemy(m_pOwner, m_vCurrentAimPosition));
//				}else
//				{
//					if (TargetMgr->isTheFakeClosestBulletDangerous(m_pOwner, 
//						enemyPos, dirToMyTank, GetBulletSpeedByTankType(typeEnemy)))
//					{
//						AddSubgoal(new GoalCover(m_pOwner, TargetMgr->GetAllAliveEnemyPositions()));
//					}else
//					{
//						AddSubgoal(new GoalShootEnemy(m_pOwner, m_vCurrentAimPosition));
//					}
//				}
//			}
			AddSubgoal(new GoalShootEnemy(m_pOwner, m_vCurrentAimPosition));
		}
	}
	else
	{
		AddSubgoal(new GoalGoToPosToAttackEnemy(m_pOwner, m_vCurrentAimPosition));
	}	
}

int GoalHuntEnemy::Process()
{
	//if see enemy then attack.
	ActivateIfInactive();
	m_iStatus = ProcessSubgoals();
	ReactivateIfFailed();
	return m_iStatus;
}

void GoalHuntEnemy::Terminate()
{
//	m_pOwner->MoveOff();
}
