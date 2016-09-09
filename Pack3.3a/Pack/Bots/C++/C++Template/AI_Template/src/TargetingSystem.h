#pragma once
#include "MyTank.h"
#include <ai/Bullet.h>

#define TargetMgr TargetingSystem::GetInstance() 

class MyTank;

class TargetingSystem
{
public:
	TargetingSystem();
	~TargetingSystem();

	bool isShootableAEnemy(glm::vec2 checkPosition, glm::vec2 enemyPosition);
	bool isShootableBase(glm::vec2 checkPosition, glm::vec2 enemyBasePositon);
	bool isEmptyBetweenPoints(glm::vec2 p1, glm::vec2 p2, std::vector<int> typeBlocks);
	bool isEmptyBetweenTwoPoints(glm::vec2 p1, glm::vec2 p2, std::vector<int> typeBlocks);

	/*fucntions for attack enemy*/
	glm::vec2 GetBestEnemyTargetPositionToAttack(MyTank* myTank);
	glm::vec2 GetBestPositionForSniperToAttack(MyTank* myTank, glm::vec2 enemyPosition);
	glm::vec2 GetBestPositionForSniperToReaload(MyTank* myTank);
	
	std::vector<glm::vec2> GetPositionsForAttackEnemy(MyTank* myTank, glm::vec2 enemyPosition);
	std::vector<glm::vec2> GetSafePositionsForEvaluation(MyTank* myTank);
	std::vector<glm::vec2> GenarateGroundedPositionsUsingBFS(glm::vec2 root, int numPositions);
	std::vector<glm::vec2> GetGroundAjacentPositions(glm::vec2 position);

	/*functions for attack main base*/
	std::vector<glm::vec2> GetEnemyMainBasePositions();
	std::vector<glm::vec2> GetEnemySideBasePositions();
	glm::vec2 GetBestTargetMainBasePosition(MyTank* myTank);
	glm::vec2 GetBestPositionToAttackMainBase(MyTank* myTank, glm::vec2 mainBaseTargetPosition);
	std::vector<glm::vec2> GetPositionsCanAttackMainBase(MyTank* myTank, glm::vec2 mainBaseTargetPosition);
	glm::vec2 GetMyMainBasePosition();

	/*functions for dodge bullets*/
	std::vector<Bullet*> GetAllDangerBulletPositions(glm::vec2 tankPosition);
	Bullet* GetClosestDangerBullet(glm::vec2 tankPosition);
	bool isTheClosestBulletDangerous(MyTank* myTank, Bullet* closestBullet);
	float GetDistanceFromAInViewBulletToATank(glm::vec2 tankPos, glm::vec2 bulletPos, glm::vec2 bulletDir);
	int GetTimeAInViewBulletToHitATank(glm::vec2 tankPos, glm::vec2 bulletPos, glm::vec2 bulletDir, float bulletSpeed);
	float CalculateDistanceToDodgeBulletByDir(glm::vec2 tankPos, glm::vec2 bulletPos, glm::vec2 bulletDir, glm::vec2 dodgeDir);
	int CalculateTimeToDodgeByDistance(float speed, float distance);
	bool isPossibleToMoveByDirAndTime(glm::vec2 tankPos, float tankSpeed, glm::vec2 dirToMove, int timeToMove);
	

	/*Helpful functions*/
	void ChoseEnemyToTarget(int enemyId);
	void UnchoseEnemyToTarget(int enemyId);
	int GetEnemyIdMostChosen();
	int GetNumChosen(int enemyId);
	std::vector<glm::vec2> GetAllAliveEnemyPositions();
	bool isValidGroundPosition(glm::vec2 p);
	bool isValidPositionByType(glm::vec2 position, std::vector<int> types);
	std::vector<glm::vec2> GetAllTankPositions();
	bool isTheSamePositionWithOtherTank(glm::vec2 myTankPosition, glm::vec2 checkedPosition);
	
	/*Check valid tank position*/
	bool isValidTankPosition(glm::vec2 tankPos);
	std::vector<int> ExtractCoordinate(float xOrY);
	std::vector<glm::vec2> GetAllIntegerPositionsTankOverLap(glm::vec2 tankPos);

	static TargetingSystem* GetInstance();
private:
	std::vector<glm::vec2> m_vEnemyMainBasePositions;
	std::vector<glm::vec2> m_vEnemySideBasePositions;
	std::vector<int> m_vChosenEnemyInfo;
	int m_iRandomMainBaseTarget;
};
