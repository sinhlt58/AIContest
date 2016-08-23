#pragma once
#include "include/ai/Tank.h"
#include "glm/vec2.hpp"
#include "SteeringBehavior.h"
#include "PathPlanner.h"
#include "GoalThink.h"
#include "VisionSystem.h"

class Tank;
class SteeringBehavior;
class PathPlanner;
class GoalThink;
class VisionSystem;

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
	int ID()const { return m_iId; }
private:
	int m_iId;

	//Steering behavior.
	SteeringBehavior* m_pSteeringBehavior;

	//Path planner uses  A* to find path.
	PathPlanner* m_pPathPlanner;

	//Helps to chose wich goal depends on situation.
	GoalThink* m_pBrain;

	//How this tank sees enemies.
	VisionSystem* m_pVisionSystem;

	//Target system.
};

