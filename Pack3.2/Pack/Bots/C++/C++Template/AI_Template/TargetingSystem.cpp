#include "TargetingSystem.h"
#include "include/ai/AI.h"
#include "AStarAlgorithm.h"
#include "HelperFunctions.h"
#include "Globals.h"
#include <queue>
#include "EvaluationPosition.h"

TargetingSystem::~TargetingSystem()
{
}

TargetingSystem::TargetingSystem()
{
	m_vChosenEnemyInfo = std::vector<int>(NUMBER_OF_TANK, 0);
}

std::vector<glm::vec2> TargetingSystem::GetEnemyMainBasePositions()
{
	if (s_EnemyMainBasePositions.empty())
	{
		if (AI::GetInstance()->GetMyTeam() == TEAM_1)
		{
			s_EnemyMainBasePositions.push_back(glm::vec2(19, 10));
			s_EnemyMainBasePositions.push_back(glm::vec2(20, 10));
			s_EnemyMainBasePositions.push_back(glm::vec2(19, 11));
			s_EnemyMainBasePositions.push_back(glm::vec2(20, 11));
		}
		else if (AI::GetInstance()->GetMyTeam() == TEAM_2)
		{
			s_EnemyMainBasePositions.push_back(glm::vec2(1, 10));
			s_EnemyMainBasePositions.push_back(glm::vec2(2, 10));
			s_EnemyMainBasePositions.push_back(glm::vec2(1, 11));
			s_EnemyMainBasePositions.push_back(glm::vec2(2, 11));
		}
	}
	
	return s_EnemyMainBasePositions;
}

std::vector<glm::vec2> TargetingSystem::GetEnemySideBasePositions()
{
	std::vector<glm::vec2> positions;
	if(s_EnemySideBasePositions.empty())
	{
		if (AI::GetInstance()->GetMyTeam() == TEAM_1)
		{
			s_EnemySideBasePositions.push_back(glm::vec2(17, 3));
			s_EnemySideBasePositions.push_back(glm::vec2(17, 4));
			s_EnemySideBasePositions.push_back(glm::vec2(18, 3));
			s_EnemySideBasePositions.push_back(glm::vec2(18, 4));
			s_EnemySideBasePositions.push_back(glm::vec2(17, 17));
			s_EnemySideBasePositions.push_back(glm::vec2(17, 18));
			s_EnemySideBasePositions.push_back(glm::vec2(18, 17));
			s_EnemySideBasePositions.push_back(glm::vec2(18, 18));
		}
		else if (AI::GetInstance()->GetMyTeam() == TEAM_2)
		{
			s_EnemySideBasePositions.push_back(glm::vec2(3, 3));
			s_EnemySideBasePositions.push_back(glm::vec2(3, 4));
			s_EnemySideBasePositions.push_back(glm::vec2(4, 3));
			s_EnemySideBasePositions.push_back(glm::vec2(4, 4));
			s_EnemySideBasePositions.push_back(glm::vec2(3, 17));
			s_EnemySideBasePositions.push_back(glm::vec2(3, 18));
			s_EnemySideBasePositions.push_back(glm::vec2(4, 17));
			s_EnemySideBasePositions.push_back(glm::vec2(4, 18));
		}
	}
	
	return s_EnemySideBasePositions;
}

TargetingSystem* TargetingSystem::GetInstance()
{
	static TargetingSystem instance = TargetingSystem();
	return &instance;
}

std::vector<glm::vec2> TargetingSystem::s_EnemyMainBasePositions;
std::vector<glm::vec2> TargetingSystem::s_EnemySideBasePositions;


bool TargetingSystem::isShootableAEnemy(glm::vec2 checkPosition, glm::vec2 enemyPosition)
{
	std::vector<int> blockTypes;
	blockTypes.push_back(BLOCK_HARD_OBSTACLE);
	blockTypes.push_back(BLOCK_SOFT_OBSTACLE);
	blockTypes.push_back(BLOCK_BASE);
	return isEmptyBetweenPoints(checkPosition, enemyPosition, blockTypes);
}

bool TargetingSystem::isShootableBase(glm::vec2 checkPosition, glm::vec2 enemyBasePositon)
{
	std::vector<int> blockTypes;
	blockTypes.push_back(BLOCK_HARD_OBSTACLE);
	return isEmptyBetweenPoints(checkPosition, enemyBasePositon, blockTypes);
}

bool TargetingSystem::isBulletDangerous(glm::vec2 checkPosition, glm::vec2 bulletPosition)
{
	return false;
}

bool TargetingSystem::isEmptyBetweenPoints(glm::vec2 p1, glm::vec2 p2, std::vector<int> blockTypes)
{
	int roundX1 = GetRoundPosition(p1).x;
	int roundY1 = GetRoundPosition(p1).y;
	int roundX2 = GetRoundPosition(p2).x;
	int roundY2 = GetRoundPosition(p2).y;
	int maxX, maxY, minX, minY;

	if (roundY1 == roundY2)
	{
		minX = roundX1 > roundX2 ? roundX2 : roundX1;
		maxX = roundX1 > roundX2 ? roundX1 : roundX2;
		for (int x = minX; x <= maxX; x++)
		{
			for (int type : blockTypes)
			{
				if (AI::GetInstance()->GetBlock(x, roundY1) == type)
					return false;
			}
		}
		return true;
	}
	else if (roundX1 == roundX2)
	{
		minY = roundY1 > roundY2 ? roundY2 : roundY1;
		maxY = roundY1 > roundY2 ? roundY1 : roundY2;
		for (int y = minY; y <= maxY; y++)
		{
			for (int type : blockTypes)
			{
				if (AI::GetInstance()->GetBlock(roundX1, y) == type)
					return false;
			}
		}
		return true;
	}

	return false;
}


std::vector<glm::vec2> TargetingSystem::GetPositionsForAttackEnemy(glm::vec2 enemyPosition)
{
	std::vector<glm::vec2> positions;
	glm::vec2 roundEnemyPosition = GetRoundPosition(enemyPosition);
	
	for (glm::vec2 dir : dirs)
	{
		glm::vec2 p = roundEnemyPosition + dir;
		while(isValidGroundPosition(p))
		{
			positions.push_back(p);
			p = p + dir;
		}
	}
	return positions;
}

std::vector<glm::vec2> TargetingSystem::GetSafePositionsForEvaluation(MyTank* myTank)
{
	return GenarateGroundedPositionsUsingBFS(GetRoundPosition(myTank->GetPosition()), 30);
}

std::vector<glm::vec2> TargetingSystem::GenarateGroundedPositionsUsingBFS(glm::vec2 root, int numPositions)
{
	std::vector<glm::vec2> genaratedPositions;
	std::list<glm::vec2> theFrontier;
	bool closedPositions[MAP_W][MAP_H] = { false };

	theFrontier.push_back(root);

	while(!theFrontier.empty())
	{
		glm::vec2 node = theFrontier.front();
		theFrontier.pop_front();
		int x = int(node.x);
		int y = int(node.y);
		closedPositions[x][y] = true;
		genaratedPositions.push_back(node);

		if (genaratedPositions.size() == numPositions)
			return genaratedPositions;

		for (glm::vec2 ajacentPosition : GetGroundAjacentPositions(node))
		{
			x = int(ajacentPosition.x);
			y = int(ajacentPosition.y);
			if (!closedPositions[x][y])
			{
				theFrontier.push_back(ajacentPosition);
			}
		}
	}
	return genaratedPositions;
}

bool TargetingSystem::isValidGroundPosition(glm::vec2 position)
{
	if (position.x < 0 || position.x >= MAP_W ||
		position.y < 0 || position.y >= MAP_H)
		return false;
	int typeBlock = AI::GetInstance()->GetBlock(position.x, position.y);
	if (typeBlock != BLOCK_GROUND)
		return false;
	return true;
}

std::vector<glm::vec2> TargetingSystem::GetGroundAjacentPositions(glm::vec2 position)
{
	std::vector<glm::vec2> ajacentPositions;
	for (glm::vec2 dir : dirs)
	{
		glm::vec2 p = position + dir;
		if (isValidGroundPosition(p))
			ajacentPositions.push_back(p);
	}
	return ajacentPositions;
}

glm::vec2 TargetingSystem::GetBestEnemyTargetPositionToAttack(MyTank* myTank)
{
	std::priority_queue<EvaluationPosition> pq;
	for (int i=0; i<NUMBER_OF_TANK; i++)
	{
		Tank* enemyTank = AI::GetInstance()->GetEnemyTank(i);
		if (enemyTank->GetHP() > 0)
		{
			EvaluationPosition ep = EvaluationPosition(GetRoundPosition(
								glm::vec2(enemyTank->GetX(), enemyTank->GetY())));
			ep.EvaluateDistanceToMyTankScore(myTank, 15);
			ep.EvaluateNumberOfMyTankChosenScore(i);
			pq.push(ep);
		}
	}

	if (!pq.empty())
		return pq.top().GetPosition();

	return glm::vec2();
}

glm::vec2 TargetingSystem::GetBestPositionForSniperToAttack(MyTank* myTank, glm::vec2 enemyPosition)
{
	std::vector<glm::vec2> evaluatedPositions = GetPositionsForAttackEnemy(enemyPosition);
	std::priority_queue<EvaluationPosition> pq;

	for (glm::vec2 p : evaluatedPositions)
	{
		EvaluationPosition ep = EvaluationPosition(p);
		ep.EvaluateDistanceToMyTankScore(myTank, 2);
		ep.EvaluateRangeAttackForSniperScore(enemyPosition);
		ep.EvaluateNumLineOfFireScore(-2);
		pq.push(ep);
	}

	if (!pq.empty())
		return pq.top().GetPosition();

	return glm::vec2();
}

glm::vec2 TargetingSystem::GetBestPositionForSniperToReaload(MyTank* myTank)
{
	std::vector<glm::vec2> positionsToEvaluated = GetSafePositionsForEvaluation(myTank);
	std::priority_queue<EvaluationPosition> pq;

	for (glm::vec2 p : positionsToEvaluated)
	{
		EvaluationPosition ep = EvaluationPosition(p);
		ep.EvaluateDistanceToMyTankScore(myTank, 15);
		ep.EvaluateNumLineOfFireScore(-50);
		pq.push(ep);
	}

	if (!pq.empty())
		return pq.top().GetPosition();

	return glm::vec2();
}

void TargetingSystem::ChoseEnemyToTarget(int enemyId)
{
	m_vChosenEnemyInfo[enemyId] += 1;
}

void TargetingSystem::UnchoseEnemyToTarget(int enemyId)
{
	m_vChosenEnemyInfo[enemyId] -= 1;
}

int TargetingSystem::GetNumChosen(int enemyId)
{
	return m_vChosenEnemyInfo[enemyId];
}

std::vector<glm::vec2> TargetingSystem::GetAllAliveEnemyPositions()
{
	std::vector<glm::vec2> enemyPositions;
	for (int i=0; i< NUMBER_OF_TANK; i++)
	{
		Tank* enemyTank = AI::GetInstance()->GetEnemyTank(i);
		if (enemyTank->GetHP() > 0)
		{
			enemyPositions.push_back(glm::vec2(enemyTank->GetX(), enemyTank->GetY()));
		}
	}
	return enemyPositions;
}

int TargetingSystem::GetEnemyIdMostChosen()
{
	int mostChosen = 0;
	int mostChosenEnemyId = 0;
	for (int i=0; i<NUMBER_OF_TANK; i++)
	{
		if (m_vChosenEnemyInfo[i] > mostChosen)
		{
			mostChosen = m_vChosenEnemyInfo[i];
			mostChosenEnemyId = i;
		}
	}
	return mostChosenEnemyId;
}
