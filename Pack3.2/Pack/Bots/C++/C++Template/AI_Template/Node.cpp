#include "Node.h"
#include <vector>
#include "include/ai/defines.h"
#include "include/ai/AI.h"
#include "Globals.h"

Node::~Node()
{
}

glm::vec2 Node::GetPosition() const
{
	return m_vPosition;
}

int Node::Type() const
{
	return m_iType;
}

void Node::UpdateGscore(float s)
{
	m_fGscore = s;
}

void Node::UpdateHscore(float s)
{
	m_fHscore = s;
}

std::vector<glm::vec2> Node::GetAdjacentNodePos(int currentTankId, int targetTankId, glm::vec2 goal) const
{
	std::vector<glm::vec2> adjacentNodePos;
	
	for (glm::vec2 dir : dirs)
	{
		glm::vec2 ajacentPosition = m_vPosition + dir;
		if (isValidAdjacentPosition(ajacentPosition, currentTankId, targetTankId, goal))
		{
			adjacentNodePos.push_back(ajacentPosition);
		}
	}
	return adjacentNodePos;
}

float Node::GetPriority() const
{
	return m_fGscore + m_fHscore;
}

bool Node::operator<(const Node& right) const
{
	return GetPriority() < right.GetPriority();
}

bool Node::isValidAdjacentPosition(glm::vec2 position, int currentTankId, int targetTankId, glm::vec2 goal) const
{
	if (position == goal)
		return true;
	
	if (position.x < 0 || position.x >= MAP_W ||
		position.y < 0 || position.y >= MAP_H)
		return false;

	int typeBlock = AI::GetInstance()->GetBlock(position.x, position.y);
	if (typeBlock != BLOCK_GROUND)
		return false;

	for (int i=0; i< NUMBER_OF_TANK; i++)
	{
		Tank* teamTank = nullptr;
		Tank* enemyTank = nullptr;
		if (i != currentTankId)
		{
			teamTank = AI::GetInstance()->GetMyTank(i);
		}

		if (i != targetTankId)
		{
			enemyTank = AI::GetInstance()->GetEnemyTank(i);
		}
			
		if (teamTank)
		{
			if (abs(position.x - teamTank->GetX()) < 1 && abs(position.y - teamTank->GetY()) < 1)			
				return false;
		}
		if (enemyTank)
		{
			if (abs(position.x - enemyTank->GetX()) < 1 && abs(position.y - enemyTank->GetY()) < 1)
				return false;
		}
	}

	return true;
}

int Node::GetIndexFromPosition() const
{
	return (int(m_vPosition.y) - 1)*(MAP_W - 2) + int(m_vPosition.x - 1);
}
