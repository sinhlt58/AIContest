#pragma once
#include "ai/Tank.h"
#include "glm/vec2.hpp"
#include "SteeringBehavior.h"
#include "PathPlanner.h"
#include "GoalThink.h"
#include "VisionSystem.h"
#include "TargetingSystem.h"
#include "Regulator.h"

class Tank;
class SteeringBehavior;
class PathPlanner;
class GoalThink;
class VisionSystem;
class TargetingSystem;
class Bullet;

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
	GoalThink* GetBrain()const;
	Bullet* GetCurrentClosestDangerBullet() const { return m_pClosestDangerBullet; }
	void SetCurrentClosestDangerBullet(Bullet* p) { m_pClosestDangerBullet = p; }

	glm::vec2 GetPosition() const;
	float GetSpeed() const;
	int GetCoolDown()const;
	bool isAtPosition(glm::vec2 p) const;
	glm::vec2 m_vTmpTarget;
	int ID()const { return m_iId; }

	void FireOn() { m_bIsShoot = true; }
	void FireOff() { m_bIsShoot = false; }
	void MoveOn() { m_bIsMove = true; }
	void MoveOff() { m_bIsMove = false; }
	void SetDirection(int d) { m_iCurrentDirection = d; }

	void AimAndShootAtPosition(glm::vec2 position);
	int GetDirectionToPosition(glm::vec2 position);
	bool isEnemyInView();
	bool isShootableAEnemy(glm::vec2 enemyPosition) const;
	bool isShootableBase(glm::vec2 enemyBasePositon);
	bool isBulletDangerous(glm::vec2 bulletPosition);
	bool isSafe()const;

	/*Target enemy functions*/
	bool isCurrentEnemyTargetPresent() const
	{ return m_iCurrentTargetEnemyId != -1; }
	void SetCurrentEnemyId(int id) { m_iCurrentTargetEnemyId = id; };
	int GetCurrentEnemyId() const
	{ return m_iCurrentTargetEnemyId; }
	bool m_bIsShoot;
private:
	int m_iId;
	
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

	Regulator* m_pBrainUpdateRgulator;

	/*tmp maybe can be removed*/
	Bullet* m_pClosestDangerBullet;

	int m_iCurrentTargetEnemyId;
};

