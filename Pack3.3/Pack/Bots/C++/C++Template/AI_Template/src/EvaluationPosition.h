#pragma once
#include <glm/vec2.hpp>
#include "MyTank.h"

class MyTank;
const int BEST_RANGE_SNIPER = 6;

class EvaluationPosition
{
public:
	EvaluationPosition(glm::vec2 p) :m_fScore(0),
									 m_vPosition(p)
	{}
	~EvaluationPosition();

	
	//evaluation functions for many perpurses.
	void EvaluateNumLineOfFireScore(float weight=1);
	void EvaluateDistanceToMyTankScore(MyTank* myTank, float weight=1);
	void EvaluateDistanceToItemsScore(float weight=1);

	//evaluation functions for pick enemy target.
	void EvaluateNumberOfMyTankChosenScore(int enemyId, float weight=1);

	//evaluation functions for sniper to attack enemy.
	void EvaluateRangeAttackForSniperScore(glm::vec2 enemyPosition, float weight=1);

	bool operator<(const EvaluationPosition & right) const;
	float GetScore()const { return  m_fScore; }
	glm::vec2 GetPosition()const { return m_vPosition; }
private:
	float m_fScore;
	glm::vec2 m_vPosition;
};

