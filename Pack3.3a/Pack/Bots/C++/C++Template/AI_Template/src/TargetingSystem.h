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
	bool isBulletDangerous(glm::vec2 checkPosition, glm::vec2 bulletPosition);
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
	bool isBulletDangerous(MyTank* myTank, Bullet* bullet);
	glm::vec2 GetBestPositionToDodge(MyTank* myTank, Bullet* closestBullet);
	std::vector<glm::vec2> GetPositionsForDodgeBullet(glm::vec2 tankPos);
	glm::vec2 GetBestDirToDodge(glm::vec2 bulletPos, glm::vec2 tankPos, glm::vec2 bulletDir);

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

	static TargetingSystem* GetInstance();
private:
	std::vector<glm::vec2> m_vEnemyMainBasePositions;
	std::vector<glm::vec2> m_vEnemySideBasePositions;
	std::vector<int> m_vChosenEnemyInfo;
	int m_iRandomMainBaseTarget;
};
