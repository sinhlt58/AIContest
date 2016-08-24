#pragma once
#include "include/ai/Tank.h"
#include "glm/vec2.hpp"
#include "SteeringBehavior.h"
#include "PathPlanner.h"
#include "GoalThink.h"
#include "VisionSystem.h"
#include "TargetingSystem.h"

class Tank;
class SteeringBehavior;
class PathPlanner;
class GoalThink;
class VisionSystem;
class TargetingSystem;

class MyTank
{
public:
	MyTank(int id);
	~MyTank();
	
	void Update();
	void UpdateMovement();

	Tank* GetApiTank() const;

	
	SteeringBehavior* GetSteering() const;
	PathPlanner* GetPathPlanner() const;
	VisionSystem* GetVisionSystem()const;
	TargetingSystem* GetTargetingSystem()const;

	glm::vec2 GetPosition() const;
	bool isAtPosition(glm::vec2 p) const;
	glm::vec2 m_vTmpTarget;
	int ID()const { return m_iId; }

	void FireOn() { m_bIsShoot = true; }
	void FireOff() { m_bIsShoot = false; }
	void MoveOn() { m_bIsMove = true; }
	void MoveOff() { m_bIsMove = false; }
	void SetDirection(int d) { m_iCurrentDirection = d; }

	void AimAndShoot();
private:
	int m_iId;
	bool m_bIsShoot;
	bool m_bIsMove;
	int m_iCurrentDirection;

	//Steering behavior.
	SteeringBehavior* m_pSteeringBehavior;

	//Path planner uses  A* to find path.
	PathPlanner* m_pPathPlanner;

	//Helps to chose wich goal depends on situation.
	GoalThink* m_pBrain;

	//How this tank sees enemies.
	VisionSystem* m_pVisionSystem;

	//Target system.
	TargetingSystem* m_pTargetingSystem;
};

