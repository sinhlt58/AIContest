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
//	if (GetPosition() == glm::vec2(8, 7))
//	{
//		std::cout << "Is the fake bullet danger: " << TargetMgr->isTheFakeClosestBulletDangerous(this,
//			glm::vec2(6, 7), glm::vec2(1, 0), GetBulletSpeedByTankType(TANK_LIGHT)) << std::endl;
//	}
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
			FireOff();
			MoveOff();
			SetDirection(DIRECTION_LEFT);
		}
		for (Bullet* bullet : AI::GetInstance()->GetMyBullets())
		{
			glm::vec2 buletPos = glm::vec2(bullet->GetX(), bullet->GetY());
			if (buletPos.y == 6)
			{
//				PrintVector("My pos: ", GetPosition());
//				std::cout << "Cooldown: " << GetApiTank()->GetCoolDown() << std::endl;
//				PrintVector("Bullet pos: ", buletPos);
			}
			
		}
	}else
	{
		
	}
	
//	MoveOff();
//	FireOff();
//	std::cout << "My before final dir to go: " << m_iCurrentDirection << std::endl;
	AvoidCanNotDodgePos();
//	PrintVector("My current pos: ", GetPosition());
//	PrintVector("Target seek pos: ", m_pSteeringBehavior->m_vTarget);
//	std::cout << "My final dir to go: " << m_iCurrentDirection << std::endl;
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
	glm::vec2 aimDir = TargetMgr->GetDirInViewPointToPoint(aimPos, GetPosition());
//	glm::vec2 currentPos = GetPosition();
//	if (isPointInsideXView(currentPos, aimPos))
//	{
//		aimDir = glm::normalize(glm::vec2(aimPos.x - currentPos.x, 0));
//	}else if (isPointInsideYView(currentPos, aimPos))
//	{
//		aimDir = glm::normalize(glm::vec2(0, aimPos.y - currentPos.y));
//	}
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

int MyTank::GetType() const
{
	return GetApiTank()->GetType();
}

void MyTank::StopInTheNextStepIsDangerous()
{
	int nextDirToMove = GetSteering()->Calculate();
	glm::vec2 nextPosInTheFuture = GetPosition() +
		GetSpeed() * GetDirByDefineDir(nextDirToMove);
	Bullet* closestBullet = TargetMgr->GetClosestDangerBullet(nextPosInTheFuture);
	if (closestBullet)
	{
		GetSteering()->SeekOff();
		MoveOff();
	}
}

void MyTank::AvoidCanNotDodgePos()
{
	Tank* closestEnemyTank = TargetMgr->GetClosestEnemyTank(GetPosition());
	
	if (closestEnemyTank)
	{
//		PrintVector("Close enemy pos: ", glm::vec2(closestEnemyTank->GetX(), closestEnemyTank->GetY()));
		if (isClosestEnemyTooCloseToSniper(this, closestEnemyTank))
		{
//			PrintVector("My pos: ", GetPosition());
//			PrintVector("Too close enemy pos=================: ", glm::vec2(closestEnemyTank->GetX(), closestEnemyTank->GetY()));
			std::vector<int> goodActions = SimulateActionsToChooseGoodActions(this, closestEnemyTank);
//			for (int action : goodActions)
//			{
//				std::cout << action << " is a good action.\n";
//			}
			auto it = std::find(goodActions.begin(), goodActions.end(), m_iCurrentDirection);
			if (!goodActions.empty() && it == goodActions.end())
			{
				/*Mybe evaluate the best action here.*/
				SetDirection(goodActions[0]);
				if (goodActions[0] != DIRECTION_NONE)
					MoveOn();
				FireOff();
			}
		}
	}
}

bool MyTank::isClosestEnemyTooCloseToSniper(MyTank* myTank, Tank* enemyTank)
{
	float dangerDistance = 2.5;
	float dangerCooldown = 1;
	float distanceBetween = Manhattan(myTank->GetPosition(), 
		glm::vec2(enemyTank->GetX(), enemyTank->GetY()));
//	float distanceBetween = Manhattan(myTank->GetPosition(),
//		glm::vec2(5.5, 14));
//	std::cout << "Distance: " << distanceBetween << std::endl;
//	std::cout << "Enemy cool down: " << enemyTank->GetCoolDown() << std::endl;
	return (myTank->GetType() != TANK_HEAVY) &&
		(enemyTank->GetType() != TANK_HEAVY) &&
		distanceBetween <= dangerDistance  &&
		enemyTank->GetCoolDown() <= dangerCooldown;
}

std::vector<int> MyTank::SimulateActionsToChooseGoodActions(MyTank* myTank, Tank* enemyTank)
{
	std::vector<int> goodActions;
	for (int action : GetAllPossibleAction())
	{
		if (isThisActionIsGood(myTank, enemyTank, action))
			goodActions.push_back(action);
//		else
//			std::cout << action << " not chose!\n";
	}
	return goodActions;
}

bool MyTank::isThisActionIsGood(MyTank* myTank, Tank* enemyTank, int action)
{
	glm::vec2 myTankFuturePos = myTank->GetPosition() + 
		myTank->GetSpeed() * GetDirByDefineDir(action);
	if (TargetMgr->isValidTankPosition(myTankFuturePos))
	{
		glm::vec2 enemyPos = glm::vec2(enemyTank->GetX(), enemyTank->GetY());
//		glm::vec2 enemyPos = glm::vec2(5.5, 14);
		float bulletSpeed = GetBulletSpeedByTankType(enemyTank->GetType());
		for (int enemyAction : GetAllPossibleAction())
		{
			glm::vec2 enemyFuturePos = enemyPos + 
				enemyTank->GetSpeed() * GetDirByDefineDir(enemyAction);

			if (isTwoSquareOverLap(myTankFuturePos, enemyFuturePos))
				return false;

			if(TargetMgr->isValidTankPosition(enemyFuturePos) && 
			   TargetMgr->isShootableAEnemy(enemyFuturePos, myTankFuturePos))
			{
				glm::vec2 fakeBulletDir = 
					TargetMgr->GetDirInViewPointToPoint(myTankFuturePos, enemyFuturePos);
//				glm::vec2 fakeBulletPos = enemyFuturePos + bulletSpeed * fakeBulletDir;
				glm::vec2 fakeBulletPos = enemyFuturePos;
				if (!TargetMgr->isTheFakeClosestBulletPossibleToDodgeSideBySide(myTank->GetPosition(), myTankFuturePos, myTank->GetSpeed(),
					fakeBulletPos, fakeBulletDir, bulletSpeed))
				{
//					std::cout << "Counter action: " << enemyAction << std::endl;
//					PrintVector("My future pos: ", myTankFuturePos);
//					PrintVector("Counter enemy future pos: ", enemyFuturePos);
//					PrintVector("Fakek bullet enemy counter pos: ", fakeBulletPos);
					return false;
				}		
			}
		}
		return true;
	}
	return false;
}