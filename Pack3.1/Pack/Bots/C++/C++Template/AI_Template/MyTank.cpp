#include "MyTank.h"
#include "include/ai/Game.h"

MyTank::MyTank(int id):m_iId(id)
{
	m_pSteeringBehavior = new SteeringBehavior(this);
	m_pPathPlanner = new PathPlanner(this);
	m_pBrain = new GoalThink(this);
}

MyTank::~MyTank()
{
	delete m_pSteeringBehavior;
	delete m_pPathPlanner;
	delete m_pBrain;
}

void MyTank::Update()
{
	//update every loop.
	m_pBrain->Process();
	UpdateMovement();
}

void MyTank::UpdateMovement()
{
	int direction = m_pSteeringBehavior->Calculate();
	if (direction != DIRECTION_NONE)
	{
		Game::CommandTank(m_iId, direction, true, true);
	}else
	{
		Game::CommandTank(m_iId, DIRECTION_UP, false, true);
	}
}

Tank* MyTank::GetApiTank() const
{
	return AI::GetInstance()->GetMyTank(m_iId);
}


glm::vec2 MyTank::GetPosition() const
{
	Tank* tank = GetApiTank();
//	std::cout << "My tank: " << tank->GetX() << " " << tank->GetX() << std::endl;
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

bool MyTank::isAtPosition(glm::vec2 p) const
{
	return GetPosition().x == p.x &&
		GetPosition().y == p.y;
}
