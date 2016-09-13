#include "MyTank.h"
#include "ai/Game.h"
#include "HelperFunctions.h"
#include "Globals.h"
#include <glm/detail/func_geometric.inl>

//int numMove;
MyTank::MyTank(int id):m_iId(id),
					   m_bIsShoot(false),
					   m_bIsMove(false),
					   m_iCurrentDirection(DIRECTION_NONE)
{
	m_pSteeringBehavior = new SteeringBehavior(this);
	m_pPathPlanner = new PathPlanner(this);
	m_pBrain = new GoalThink(this);
	m_pVisionSystem = new VisionSystem(this);

	m_pBrainUpdateRgulator = new Regulator(1);
	m_pClosestDangerBullet = nullptr;

	m_iCurrentTargetEnemyId = -1;
	numMove = 0;
}

MyTank::~MyTank()
{
	delete m_pSteeringBehavior;
	delete m_pPathPlanner;
	delete m_pBrain;
	delete m_pVisionSystem;

	delete m_pBrainUpdateRgulator;
}

void MyTank::Update()
{
	//update every loop.
//	m_pVisionSystem->UpdateVision();
//	std::cout << "Inside update befor chose goal.\n";
	if(m_pBrainUpdateRgulator->isReady())
	{
		m_pBrain->Aribitrate();
	}
//	std::cout << "Inside update after chose goal.\n";
	m_pBrain->Process();
	UpdateMovement();
	if (AI::GetInstance()->GetMyTeam() == TEAM_2)
	{
		if (numMove < 0)
		{
			FireOff();
			MoveOn();
			SetDirection(DIRECTION_DOWN);
			numMove++;
		}else
		{
			FireOn();
			MoveOff();
			SetDirection(DIRECTION_LEFT);
		}
	}
	Game::CommandTank(m_iId, m_iCurrentDirection, m_bIsMove, m_bIsShoot);
	SetCurrentClosestDangerBullet(nullptr);
	SetBestDirToDodgeDangerBullet(glm::vec2());
}

void MyTank::UpdateMovement()
{
	if (AI::GetInstance()->GetMyTeam() == TEAM_1)
	{
//		FireOff();
//		m_pSteeringBehavior->SeekOn();
//		MoveOn();
//		Bullet* closestBullet = TargetMgr->GetClosestDangerBullet(GetPosition());
//		if (closestBullet)
//		{
//			MoveOn();
//			if (TargetMgr->isTheClosestBulletDangerous(this, closestBullet))
//			{
//				glm::vec2 bestDirToDodge = GetBestDirToDodgeDangerBullet();
//				glm::vec2 posToDodge = GetPosition() + bestDirToDodge * GetSpeed();
//				m_pSteeringBehavior->SetTarget(posToDodge);
//			}else
//			{
//				MoveOff();
//			}
//			
//		}
//		else
//		{
//			MoveOff();
//		}
	}
	int direction = m_pSteeringBehavior->Calculate();
//	std::cout << "Is move on: " << m_bIsMove << std::endl;
//	std::cout << "Is seek on: " << m_pSteeringBehavior->On(SteeringBehavior::seek) << std::endl;
//	PrintVector("My current pos: ", GetPosition());
//	PrintVector("Target seek pos: ", m_pSteeringBehavior->m_vTarget);
//	std::cout << "after seek calculation i have to turn: " << direction << std::endl;
	if (direction != DIRECTION_NONE && m_bIsMove)
	{
		SetDirection(direction);
	}else
	{
//		std::cout << "some reason i have to stop.\n";
	}
	
}

Tank* MyTank::GetApiTank() const
{
	return AI::GetInstance()->GetMyTank(m_iId);
}


glm::vec2 MyTank::GetPosition() const
{
	Tank* tank = GetApiTank();
	return glm::vec2(tank->GetX(), tank->GetY());
}

float MyTank::GetSpeed() const
{
	return AI::GetInstance()->GetMyTank(m_iId)->GetSpeed();
}

int MyTank::GetCoolDown() const
{
	return AI::GetInstance()->GetMyTank(m_iId)->GetCoolDown();
}

SteeringBehavior* MyTank::GetSteering() const
{
	return m_pSteeringBehavior;
}

PathPlanner* MyTank::GetPathPlanner() const
{
	return m_pPathPlanner;
}

VisionSystem* MyTank::GetVisionSystem() const
{
	return m_pVisionSystem;
}

GoalThink* MyTank::GetBrain() const
{
	return m_pBrain;
}

bool MyTank::isAtPosition(glm::vec2 p) const
{
	return GetPosition() == p;
}


void MyTank::AimAndShootAtPosition(glm::vec2 position)
{
	int aimDirection = GetDirectionToPosition(position);
	if (aimDirection != DIRECTION_NONE)
	{
		SetDirection(aimDirection);
		MoveOff();
		FireOn();
	}
}

int MyTank::GetDirectionToPosition(glm::vec2 aimPos)
{
	glm::vec2 aimDir;
	glm::vec2 currentPos = GetPosition();
	if (isPointInsideXView(currentPos, aimPos))
	{
		aimDir = glm::normalize(glm::vec2(aimPos.x - currentPos.x, 0));
	}else if (isPointInsideYView(currentPos, aimPos))
	{
		aimDir = glm::normalize(glm::vec2(0, aimPos.y - currentPos.y));
	}
	return GetDefaultDirByVectorDir(aimDir);
}

bool MyTank::isEnemyInView()
{
	return false;
}

bool MyTank::isShootableAEnemy(glm::vec2 enemyPosition) const
{
	return TargetMgr->isShootableAEnemy(GetPosition(), enemyPosition);
}

bool MyTank::isShootableBase(glm::vec2 enemyBasePositon)
{
	return TargetMgr->isShootableBase(GetPosition(), enemyBasePositon);
}

bool MyTank::isBulletDangerous(glm::vec2 bulletPosition)
{
	return false;
}

bool MyTank::isSafe() const
{
	for (glm::vec2 p : TargetMgr->GetAllAliveEnemyPositions())
	{
		if(isShootableAEnemy(p))
			return false;
	}
	
	if (TargetMgr->GetAllDangerBulletPositions(GetPosition()).size() > 0)
	{
		return false;
	}
	
	return true;
}
