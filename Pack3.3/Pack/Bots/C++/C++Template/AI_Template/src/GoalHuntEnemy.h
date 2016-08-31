#pragma once
#include "GoalComposite.h"
#include "MyTank.h"

class MyTank;

class GoalHuntEnemy : public GoalComposite<MyTank>
{
public:
	GoalHuntEnemy(MyTank* pOwner);
	~GoalHuntEnemy();

	void Activate() override;
	int Process() override;
	void Terminate() override;

private:
	glm::vec2 m_vCurrentAimPosition;
	glm::vec2 m_vCurrentGoodPosition;
};

