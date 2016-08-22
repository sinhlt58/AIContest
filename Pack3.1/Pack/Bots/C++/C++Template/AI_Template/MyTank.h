#pragma once
#include "include/ai/Tank.h"
#include "glm/vec2.hpp"
#include "SteeringBehavior.h"
#include "PathPlanner.h"
#include "GoalThink.h"

class Tank;
class SteeringBehavior;
class PathPlanner;
class GoalThink;

class MyTank
{
public:
	MyTank(int id);
	~MyTank();
	
	void Update();
	void UpdateMovement();

	Tank* GetApiTank() const;

	glm::vec2 GetPosition() const;
	SteeringBehavior* GetSteering() const;
	PathPlanner* GetPathPlanner() const;
	bool isAtPosition(glm::vec2 p) const;
	glm::vec2 m_vTmpTarget;
private:
	int m_iId;

	//Steering behavior.
	SteeringBehavior* m_pSteeringBehavior;

	PathPlanner* m_pPathPlanner;

	//Brain.
	GoalThink* m_pBrain;

	//Target system.
};

