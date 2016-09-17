#pragma once
#include "MyTank.h"

class MyTank;

class GoalDodgeStrike : public GoalComposite<MyTank>
{
public:
	GoalDodgeStrike(MyTank* pOwner);
	~GoalDodgeStrike();

	void Activate() override;
	int Process() override;
	void Terminate() override;
};