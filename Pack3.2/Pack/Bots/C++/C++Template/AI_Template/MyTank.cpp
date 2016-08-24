#include "MyTank.h"
#include "include/ai/Game.h"

MyTank::MyTank(int id):m_iId(id),
					   m_bIsShoot(false),
					   m_bIsMove(false),
					   m_iCurrentDirection(DIRECTION_NONE)
{
	m_pSteeringBehavior = new SteeringBehavior(this);
	m_pPathPlanner = new PathPlanner(this);
	m_pBrain = new GoalThink(this);
	m_pVisionSystem = new VisionSystem(this);
	m_pTargetingSystem = new TargetingSystem(this);
}

MyTank::~MyTank()
{
	delete m_pSteeringBehavior;
	delete m_pPathPlanner;
	delete m_pBrain;
	delete m_pVisionSystem;
	delete m_pTargetingSystem;
}

void MyTank::Update()
{
	//update every loop.
	m_pBrain->Process();
	UpdateMovement();
	m_pVisionSystem->UpdateVision();
	m_pTargetingSystem->Update();
	AimAndShoot();

	Game::CommandTank(m_iId, m_iCurrentDirection, m_bIsMove, m_bIsShoot);
}

void MyTank::UpdateMovement()
{
	int direction = m_pSteeringBehavior->Calculate();
	if (direction != DIRECTION_NONE)
	{
		MoveOn();
		SetDirection(direction);
	}else
	{
		MoveOff();
		SetDirection(DIRECTION_UP);
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

TargetingSystem* MyTank::GetTargetingSystem() const
{
	return m_pTargetingSystem;
}

bool MyTank::isAtPosition(glm::vec2 p) const
{
	return GetPosition() == p;
}

void MyTank::AimAndShoot()
{
	if (m_pTargetingSystem->isTargetingEnemyPresent() 
		&& m_pTargetingSystem->isTargetingEnemyShootable())
	{
		//aim here
		int aimDirection = m_pTargetingSystem->GetAimDirection();
		cout << "aim direction: " << aimDirection << endl;
		SetDirection(aimDirection);
		FireOn();
		MoveOff();
	}
}
