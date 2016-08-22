#pragma once
#include "GoalComposite.h"
#include "MyTank.h"

class MyTank;

class GoalThink : public GoalComposite<MyTank>
{
public:
	GoalThink(MyTank* pOwner);
	~GoalThink();

	void Aribitrate();
	bool notPresent(unsigned int goalType) const;

	void Activate() override;
	int Process() override;
	void Terminate() override;
};

