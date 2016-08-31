#pragma once
#include "MyTank.h"

#define TargetMgr TargetingSystem::GetInstance() 

class MyTank;

class TargetingSystem
{
public:
	TargetingSystem();
	~TargetingSystem();

	static std::vector<glm::vec2> GetEnemyMainBasePositions();
	static std::vector<glm::vec2> GetEnemySideBasePositions();

	bool isShootableAEnemy(glm::vec2 checkPosition, glm::vec2 enemyPosition);
	bool isShootableBase(glm::vec2 checkPosition, glm::vec2 enemyBasePositon);
	bool isBulletDangerous(glm::vec2 checkPosition, glm::vec2 bulletPosition);
	bool isEmptyBetweenPoints(glm::vec2 p1, glm::vec2 p2, std::vector<int> typeBlocks);

	glm::vec2 GetBestEnemyTargetPositionToAttack(MyTank* myTank);
	glm::vec2 GetBestPositionForSniperToAttack(MyTank* myTank, glm::vec2 enemyPosition);
	glm::vec2 GetBestPositionForSniperToReaload(MyTank* myTank);

	std::vector<glm::vec2> GetPositionsForAttackEnemy(glm::vec2 enemyPosition);
	std::vector<glm::vec2> GetSafePositionsForEvaluation(MyTank* myTank);
	std::vector<glm::vec2> GenarateGroundedPositionsUsingBFS(glm::vec2 root, int numPositions);
	bool isValidGroundPosition(glm::vec2 p);
	std::vector<glm::vec2> GetGroundAjacentPositions(glm::vec2 position);

	static TargetingSystem* GetInstance();

	void ChoseEnemyToTarget(int enemyId);
	void UnchoseEnemyToTarget(int enemyId);
	int GetEnemyIdMostChosen();
	int GetNumChosen(int enemyId);
	std::vector<glm::vec2> GetAllAliveEnemyPositions();
private:
	static  std::vector<glm::vec2> s_EnemyMainBasePositions;
	static  std::vector<glm::vec2> s_EnemySideBasePositions;
	std::vector<int> m_vChosenEnemyInfo;
};
