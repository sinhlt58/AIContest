#include "MyTank.h"
#include "include/ai/Game.h"

MyTank::MyTank(int id):m_iId(id)
{
	m_pSteeringBehavior = new SteeringBehavior(this);
	m_pPathPlanner = new PathPlanner(this);
}

MyTank::~MyTank()
{
	delete m_pSteeringBehavior;
	delete m_pPathPlanner;
}

void MyTank::Update()
{
	//update every loop.
	UpdateMovement();
//	int direction = m_pSteeringBehavior->Calculate();
//	Game::CommandTank(m_iId, direction, true, false);
}

void MyTank::UpdateMovement()
{
	int direction = m_pSteeringBehavior->Calculate();
	if (direction != DIRECTION_NONE)
	{
		Game::CommandTank(m_iId, direction, true, false);
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
