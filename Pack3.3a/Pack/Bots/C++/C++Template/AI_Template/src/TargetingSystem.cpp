#include "TargetingSystem.h"
#include "ai/AI.h"
#include "AStarAlgorithm.h"
#include "HelperFunctions.h"
#include "Globals.h"
#include <queue>
#include "EvaluationPosition.h"
#include <glm/detail/func_geometric.inl>

TargetingSystem::~TargetingSystem()
{
}

TargetingSystem::TargetingSystem()
{
	m_vChosenEnemyInfo = std::vector<int>(NUMBER_OF_TANK, 0);
	m_iRandomMainBaseTarget = rand() % 4;

	if (AI::GetInstance()->GetMyTeam() == TEAM_1)
	{
		m_vEnemyMainBasePositions.push_back(glm::vec2(20, 10));
		m_vEnemyMainBasePositions.push_back(glm::vec2(20, 11));
		m_vEnemyMainBasePositions.push_back(glm::vec2(19, 10));
		m_vEnemyMainBasePositions.push_back(glm::vec2(19, 11));

		m_vEnemySideBasePositions.push_back(glm::vec2(17, 3));
		m_vEnemySideBasePositions.push_back(glm::vec2(17, 4));
		m_vEnemySideBasePositions.push_back(glm::vec2(18, 3));
		m_vEnemySideBasePositions.push_back(glm::vec2(18, 4));
		m_vEnemySideBasePositions.push_back(glm::vec2(17, 17));
		m_vEnemySideBasePositions.push_back(glm::vec2(17, 18));
		m_vEnemySideBasePositions.push_back(glm::vec2(18, 17));
		m_vEnemySideBasePositions.push_back(glm::vec2(18, 18));
	}
	else if (AI::GetInstance()->GetMyTeam() == TEAM_2)
	{
		m_vEnemyMainBasePositions.push_back(glm::vec2(1, 10));
		m_vEnemyMainBasePositions.push_back(glm::vec2(2, 10));
		m_vEnemyMainBasePositions.push_back(glm::vec2(1, 11));
		m_vEnemyMainBasePositions.push_back(glm::vec2(2, 11));

		m_vEnemySideBasePositions.push_back(glm::vec2(3, 3));
		m_vEnemySideBasePositions.push_back(glm::vec2(3, 4));
		m_vEnemySideBasePositions.push_back(glm::vec2(4, 3));
		m_vEnemySideBasePositions.push_back(glm::vec2(4, 4));
		m_vEnemySideBasePositions.push_back(glm::vec2(3, 17));
		m_vEnemySideBasePositions.push_back(glm::vec2(3, 18));
		m_vEnemySideBasePositions.push_back(glm::vec2(4, 17));
		m_vEnemySideBasePositions.push_back(glm::vec2(4, 18));
	}
}

std::vector<glm::vec2> TargetingSystem::GetEnemyMainBasePositions()
{
	return m_vEnemyMainBasePositions;
}

std::vector<glm::vec2> TargetingSystem::GetEnemySideBasePositions()
{
	return m_vEnemySideBasePositions;
}

TargetingSystem* TargetingSystem::GetInstance()
{
	static TargetingSystem instance = TargetingSystem();
	return &instance;
}


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
	float halfTankWidth = 0.5;
	if (isTankInViewX(p1, p2))
	{
		if (!isSpecialDividedByOneHalf(p1.y) && !isSpecialDividedByOneHalf(p2.y))
		{
			return isEmptyBetweenTwoPoints(p1, p2, blockTypes);
		}else if (!isSpecialDividedByOneHalf(p1.y) && isSpecialDividedByOneHalf(p2.y))
		{
			glm::vec2 roundP1 = GetRoundPosition(p1);
			if (roundP1.y == p2.y - halfTankWidth)
			{
				return isEmptyBetweenTwoPoints(p1, glm::vec2(p2.x, p2.y - halfTankWidth), blockTypes);
			}else if (roundP1.y == p2.y + halfTankWidth)
			{
				return isEmptyBetweenTwoPoints(p1, glm::vec2(p2.x, p2.y + halfTankWidth), blockTypes);
			}
		}else if(isSpecialDividedByOneHalf(p1.y) && !isSpecialDividedByOneHalf(p2.y))
		{
			glm::vec2 roundP2 = GetRoundPosition(p2);
			if (roundP2.y == p1.y - halfTankWidth)
			{
				return isEmptyBetweenTwoPoints(p2, glm::vec2(p1.x, p1.y - halfTankWidth), blockTypes);
			}
			else if (roundP2.y == p1.y + halfTankWidth)
			{
				return isEmptyBetweenTwoPoints(p2, glm::vec2(p1.x, p1.y + halfTankWidth), blockTypes);
			}
		}else
		{
			return isEmptyBetweenTwoPoints(glm::vec2(p1.x, p1.y - halfTankWidth), glm::vec2(p2.x, p2.y - halfTankWidth), blockTypes)
				&& isEmptyBetweenTwoPoints(glm::vec2(p1.x, p1.y + halfTankWidth), glm::vec2(p2.x, p2.y + halfTankWidth), blockTypes);
		}
	}else if(isTankInViewY(p1, p2))
	{
		if (!isSpecialDividedByOneHalf(p1.x) && !isSpecialDividedByOneHalf(p2.x))
		{
			return isEmptyBetweenTwoPoints(p1, p2, blockTypes);
		}
		else if (!isSpecialDividedByOneHalf(p1.x) && isSpecialDividedByOneHalf(p2.x))
		{
			glm::vec2 roundP1 = GetRoundPosition(p1);
			if (roundP1.x == p2.x - halfTankWidth)
			{
				return isEmptyBetweenTwoPoints(p1, glm::vec2(p2.x - halfTankWidth, p2.y), blockTypes);
			}
			else if (roundP1.x == p2.x + halfTankWidth)
			{
				return isEmptyBetweenTwoPoints(p1, glm::vec2(p2.x + halfTankWidth, p2.y), blockTypes);
			}
		}
		else if (isSpecialDividedByOneHalf(p1.x) && !isSpecialDividedByOneHalf(p2.x))
		{
			glm::vec2 roundP2 = GetRoundPosition(p2);
			if (roundP2.x == p1.x - halfTankWidth)
			{
				return isEmptyBetweenTwoPoints(p2, glm::vec2(p1.x - halfTankWidth, p1.y), blockTypes);
			}
			else if (roundP2.x == p1.x + halfTankWidth)
			{
				return isEmptyBetweenTwoPoints(p2, glm::vec2(p1.x + halfTankWidth, p1.y), blockTypes);
			}
		}
		else
		{
			return isEmptyBetweenTwoPoints(glm::vec2(p1.x - halfTankWidth, p1.y), glm::vec2(p2.x - halfTankWidth, p2.y), blockTypes)
				&& isEmptyBetweenTwoPoints(glm::vec2(p1.x + halfTankWidth, p1.y), glm::vec2(p2.x + halfTankWidth, p2.y), blockTypes);
		}
	}
	return false;
}

bool TargetingSystem::isEmptyBetweenTwoPoints(glm::vec2 p1, glm::vec2 p2, std::vector<int> blockTypes)
{
	int roundX1 = GetRoundPosition(p1).x;
	int roundY1 = GetRoundPosition(p1).y;
	int roundX2 = GetRoundPosition(p2).x;
	int roundY2 = GetRoundPosition(p2).y;
	int maxX, maxY, minX, minY;

	if (!isPointInsideXView(p1, p2) && !isPointInsideYView(p1, p2))
		return false;

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

std::vector<glm::vec2> TargetingSystem::GetPositionsForAttackEnemy(MyTank* myTank, glm::vec2 enemyPosition)
{
//	std::vector<glm::vec2> positions;
//	glm::vec2 roundEnemyPosition = GetRoundPosition(enemyPosition);
//	
//	for (glm::vec2 dir : dirs)
//	{
//		glm::vec2 p = roundEnemyPosition + dir;
//		while(isValidGroundPosition(p))
//		{
//			if (!isTheSamePositionWithOtherTank(myTank->GetPosition(), p))
//				positions.push_back(p);
//			p = p + dir;
//		}
//	}
//
//	return positions;
	return GenarateGroundedPositionsUsingBFS(enemyPosition, 30);
}

std::vector<glm::vec2> TargetingSystem::GetSafePositionsForEvaluation(MyTank* myTank)
{
	return GenarateGroundedPositionsUsingBFS(GetRoundPosition(myTank->GetPosition()), 40);
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
	std::vector<int> types;
	types.push_back(BLOCK_GROUND);
	return isValidPositionByType(position, types);
}

bool TargetingSystem::isValidPositionByType(glm::vec2 position, std::vector<int> types)
{
	if (position.x < 0 || position.x >= MAP_W ||
		position.y < 0 || position.y >= MAP_H)
		return false;
	int typeBlock = AI::GetInstance()->GetBlock(position.x, position.y);
	for (int type : types)
	{
		if (typeBlock == type)
			return true;
	}
	return false;
}

std::vector<glm::vec2> TargetingSystem::GetAllTankPositions()
{
	std::vector<glm::vec2> positions;
	for (int i=0; i<NUMBER_OF_TANK; i++)
	{
		Tank* teamTank = nullptr;
		Tank* enemyTank = nullptr;
	
		teamTank = AI::GetInstance()->GetMyTank(i);
		enemyTank = AI::GetInstance()->GetEnemyTank(i);

		if (teamTank)
		{
			positions.push_back(glm::vec2(teamTank->GetX(), teamTank->GetY()));
		}
		if (enemyTank)
		{
			positions.push_back(glm::vec2(enemyTank->GetX(), enemyTank->GetY()));
		}
	}
	return positions;
}

bool TargetingSystem::isTheSamePositionWithOtherTank(glm::vec2 myTankPosition, glm::vec2 checkedPosition)
{
	for (glm::vec2 p : GetAllTankPositions())
	{
		if (p != myTankPosition)
		{
			if (isTwoSquareOverLap(checkedPosition, p))
			{
				return true;
			}		
		}
	}
	return false;
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
			glm::vec2 enemyPos = glm::vec2(enemyTank->GetX(), enemyTank->GetY());
			EvaluationPosition ep = EvaluationPosition(enemyPos);
			ep.EvaluateDistanceToMyTankScore(myTank, 10);
			ep.EvaluateCloseToMainBase(GetMyMainBasePosition(), 300);
//			ep.EvaluateShootableEnemy(myTank->GetPosition(), 10);
//			ep.EvaluateNumberOfMyTankChosenScore(i, 15);
			ep.SetTargetEnemyId(i);//this is a little bit dump ##!.
			pq.push(ep);
		}
	}

	if (!pq.empty())
	{
		myTank->SetCurrentEnemyId(pq.top().GetTargetEnemyId());
		ChoseEnemyToTarget(pq.top().GetTargetEnemyId());
		return pq.top().GetPosition();
	}
		
	return glm::vec2();
}

glm::vec2 TargetingSystem::GetBestPositionForSniperToAttack(MyTank* myTank, glm::vec2 enemyPosition)
{
	std::vector<glm::vec2> evaluatedPositions = GetPositionsForAttackEnemy(myTank, enemyPosition);
	std::priority_queue<EvaluationPosition> pq;

	for (glm::vec2 p : evaluatedPositions)
	{
		if (!isTheSamePositionWithOtherTank(myTank->GetPosition(), p))
		{
			EvaluationPosition ep = EvaluationPosition(p);
			ep.EvaluateDistanceToMyTankScore(myTank, 10);
			ep.EvaluateRangeAttackForSniperScore(enemyPosition, 10);
			ep.EvaluateNumLineOfFireScore(5);
			ep.EvaluateDangerouseBullets(-50);
			pq.push(ep);
		}		
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
		if (!isTheSamePositionWithOtherTank(myTank->GetPosition(), p))
		{
			EvaluationPosition ep = EvaluationPosition(p);
			ep.EvaluateDistanceToMyTankScore(myTank, 10);
			ep.EvaluateNumLineOfFireScore(-10);
			ep.EvaluateDangerouseBullets(-50);
			ep.EvaluateCloseToMainBase(TargetMgr->GetMyMainBasePosition(), 5);
//			ep.EvaluateOrthogonalWithMyTankScore(myTank->GetPosition(), 5);
			//		if (myTank->isCurrentEnemyTargetPresent())
			//		{
			//			Tank* enemyTank = AI::GetInstance()->GetEnemyTank(myTank->GetCurrentEnemyId());
			//			glm::vec2 enemyPosition = glm::vec2(enemyTank->GetX(), enemyTank->GetY());
			//			ep.EvaluateCloserToEnemyToReload(enemyPosition, 25);
			//		}
			pq.push(ep);
		}
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

/*Functions for attack main base*/
glm::vec2 TargetingSystem::GetBestTargetMainBasePosition(MyTank* myTank)
{
	return GetEnemyMainBasePositions()[m_iRandomMainBaseTarget];
}

glm::vec2 TargetingSystem::GetBestPositionToAttackMainBase(MyTank* myTank, glm::vec2 mainBaseTargetPosition)
{
	std::vector<glm::vec2> positionsToAttack = GetPositionsCanAttackMainBase(myTank, mainBaseTargetPosition);
	std::priority_queue<EvaluationPosition> pq;

	for (glm::vec2 p : positionsToAttack)
	{
		EvaluationPosition ep = EvaluationPosition(p);
		ep.EvaluateDistanceToEnemyBaseTarget(mainBaseTargetPosition);
		ep.EvaluateSameXAxisWithBaseTarget(mainBaseTargetPosition);
		ep.EvaluateWithCenter(mainBaseTargetPosition, 2);
		pq.push(ep);
	}

	if (!pq.empty())
		return pq.top().GetPosition();

	return glm::vec2();
}

std::vector<glm::vec2> TargetingSystem::GetPositionsCanAttackMainBase(MyTank* myTank, glm::vec2 mainBaseTargetPosition)
{
	std::vector<glm::vec2> attackablePositions;
	std::vector<glm::vec2> resultPositions;
	std::vector<int> validTypes;
	validTypes.push_back(BLOCK_GROUND);
	validTypes.push_back(BLOCK_BASE);
	validTypes.push_back(BLOCK_SOFT_OBSTACLE);
	for (glm::vec2 dir : dirs)
	{
		glm::vec2 p = mainBaseTargetPosition + dir;
		while(isValidPositionByType(p, validTypes))
		{
			attackablePositions.push_back(p);
			p = p + dir;
		}
	}
	for (glm::vec2 p : attackablePositions)
	{
		if (isValidGroundPosition(p) && !isTheSamePositionWithOtherTank(myTank->GetPosition(), p))
			resultPositions.push_back(p);
	}
	return resultPositions;
}

glm::vec2 TargetingSystem::GetMyMainBasePosition()
{
	if (AI::GetInstance()->GetMyTeam() == TEAM_1)
	{
		return glm::vec2(1.5, 10.5);
	}
	if (AI::GetInstance()->GetMyTeam() == TEAM_2)
	{
		return glm::vec2(19.5, 10.5);
	}
	return glm::vec2();
}

std::vector<Bullet*> TargetingSystem::GetAllDangerBulletPositions(glm::vec2 tankPosition)
{
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> enemyBullets = AI::GetInstance()->GetEnemyBullets();

	for (Bullet* bullet : enemyBullets)
	{
		glm::vec2 bulletPos = glm::vec2(bullet->GetX(), bullet->GetY());
		if (isInView(bulletPos, tankPosition))
		{
			glm::vec2 bulletDir = GetDirByDefineDir(bullet->GetDirection());
			glm::vec2 vecBulletToTankPos;
			glm::vec2 sum;
			if (isPointInsideXView(bulletPos, tankPosition))
			{
				vecBulletToTankPos = glm::vec2(bulletPos.x - tankPosition.x, 0);
			}else if(isPointInsideYView(bulletPos, tankPosition))
			{
				vecBulletToTankPos = glm::vec2(0, bulletPos.y - tankPosition.y);
			}
			if (glm::length(vecBulletToTankPos) > 0)
			{
				vecBulletToTankPos = glm::normalize(vecBulletToTankPos);
				sum = bulletDir + vecBulletToTankPos;
				if (sum == glm::vec2())
				{
					bullets.push_back(bullet);
//					PrintVector("Dangerous bullet: ", bulletPos);
				}
			}	
		}else
		{
//			PrintVector("Not dangerous bullet: ", bulletPos);
//			std::cout << "Type: " << bullet->GetType() << std::endl;
		}
	}

	return bullets;
}

Bullet* TargetingSystem::GetClosestDangerBullet(glm::vec2 tankPosition)
{
	std::vector<Bullet*> bullets = GetAllDangerBulletPositions(tankPosition);
	if(!bullets.empty())
	{
		Bullet* closetBullet = bullets[0];
		float closet = 9999;
		for (Bullet* bullet : bullets)
		{
			if (glm::length(glm::vec2(bullet->GetX(),bullet->GetY())) < closet)
				closetBullet = bullet;
		}
		return closetBullet;
	}
	return nullptr;
}

bool TargetingSystem::isBulletDangerous(MyTank* myTank, Bullet* closestBullet)
{
	glm::vec2 tankPosition = myTank->GetPosition();
	glm::vec2 bulletPosition = glm::vec2(closestBullet->GetX(), closestBullet->GetY());
	glm::vec2 bulletDir = GetDirByDefineDir(closestBullet->GetDirection());
	glm::vec2 vecBulletToPosition = bulletPosition - tankPosition;
	float distanceFromBulletToTank = 0;
	float distanceNeedToDodge = 0;
	float widthOfBullet = 0;
	float halfTankWidth = 0.5;
	float timeBulletToTravel = 0;
	float timeToDodge = 0;
	float noise = 0;

	if (glm::length(vecBulletToPosition) > 0)
	{
		if (isPointInsideXView(bulletPosition, tankPosition))
		{
			distanceFromBulletToTank = abs(vecBulletToPosition.x) - halfTankWidth;
			distanceNeedToDodge = halfTankWidth - abs(vecBulletToPosition.y) + widthOfBullet;
		}else if(isPointInsideYView(bulletPosition, tankPosition))
		{
			distanceFromBulletToTank = abs(vecBulletToPosition.y) - halfTankWidth;
			distanceNeedToDodge = halfTankWidth - abs(vecBulletToPosition.x) + widthOfBullet;
		}
		timeBulletToTravel = distanceFromBulletToTank / closestBullet->GetSpeed();
		timeToDodge = distanceNeedToDodge / myTank->GetSpeed();
		if (timeToDodge >= timeBulletToTravel)
			return true;
		return false;
	}
	return true;
}

glm::vec2 TargetingSystem::GetBestPositionToDodge(MyTank* myTank, Bullet* closestBullet)
{
	glm::vec2 tankPosition = myTank->GetPosition();
	glm::vec2 bulletPosition = glm::vec2(closestBullet->GetX(), closestBullet->GetY());
	glm::vec2 bulletDir = GetDirByDefineDir(closestBullet->GetDirection());

	std::vector<glm::vec2> positionsToEvaluated = GetPositionsForDodgeBullet(myTank->GetPosition());
	std::priority_queue<EvaluationPosition> pq;

	for (glm::vec2 p : positionsToEvaluated)
	{
		EvaluationPosition ep = EvaluationPosition(p);
		ep.EvaluateDistanceToMyTankScore(myTank, 2);
//		ep.EvaluateNumLineOfFireScore(-2);
		ep.EvaluateOrthogonalScore(bulletDir, myTank->GetPosition(), 2);
		ep.EvaluateBestDirToDodgeScore(tankPosition, GetBestDirToDodge(bulletPosition, tankPosition, bulletDir), 10);
		pq.push(ep);
	}

	if (!pq.empty())
		return pq.top().GetPosition();

	return glm::vec2();
}

std::vector<glm::vec2> TargetingSystem::GetPositionsForDodgeBullet(glm::vec2 tankPos)
{
	std::vector<glm::vec2> positions;
	for (glm::vec2 dir : dirs)
	{
		glm::vec2 p = tankPos + dir;
		while (isValidGroundPosition(GetRoundPosition(p)))
		{
			positions.push_back(p);
			p = p + dir;
		}
	}
	return positions;
}

glm::vec2 TargetingSystem::GetBestDirToDodge(glm::vec2 bulletPos, glm::vec2 tankPos, glm::vec2 bulletDir)
{
	glm::vec2 vecBulletToTank = bulletPos - tankPos;
	glm::vec2 bestDirToDodge;
	if (glm::length(vecBulletToTank) > 0)
	{
		if (bulletDir.x == 0)
		{
			if (vecBulletToTank.x != 0)
				bestDirToDodge = glm::normalize(glm::vec2(-vecBulletToTank.x, 0));
			else
				bestDirToDodge = glm::vec2(1, 0);
		}
		else if (bulletDir.y == 0)
		{
			if (vecBulletToTank.y != 0)
				bestDirToDodge = glm::normalize(glm::vec2(0, -vecBulletToTank.y));
			else
				bestDirToDodge = glm::vec2(0, 1);
		}
	}
	return bestDirToDodge;
}
