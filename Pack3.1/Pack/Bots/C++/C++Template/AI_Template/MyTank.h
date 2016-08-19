#pragma once
#include "include/ai/Tank.h"
#include "glm/vec2.hpp"
#include "SteeringBehavior.h"
#include "PathPlanner.h"

class Tank;
class SteeringBehavior;
class PathPlanner;

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
private:
	int m_iId;

	//Steering behavior.
	SteeringBehavior* m_pSteeringBehavior;

	PathPlanner* m_pPathPlanner;

	//Brain.

	//Target system.
};

