#pragma once
#include "GoalEvaluator.h"
#include "MyTank.h"

class MyTank;

class EvaluatorHuntEnemy : public GoalEvaluator
{
public:
	EvaluatorHuntEnemy(float bias):GoalEvaluator(bias)
	{}
	~EvaluatorHuntEnemy();

	float CalculateDesirability(MyTank* pTank) override;
	void SetGoal(MyTank* pTank) override;
};

