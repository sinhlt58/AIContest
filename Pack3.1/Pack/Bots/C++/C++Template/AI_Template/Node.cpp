#include "Node.h"
#include <vector>
#include "include/ai/defines.h"
#include "include/ai/AI.h"

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

std::vector<glm::vec2> Node::GetAdjacentNodePos() const
{
	std::vector<glm::vec2> adjacentNodePos;
	
	for (glm::vec2 dir : dirs)
	{
		glm::vec2 ajacentPosition = m_vPosition + dir;
		if (isValidAdjacentPosition(ajacentPosition))
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
	return GetPriority() > right.GetPriority();
}

bool Node::isValidAdjacentPosition(glm::vec2 position) const
{
	if (position.x < 0 || position.x >= MAP_W ||
		position.y < 0 || position.y >= MAP_H)
		return false;

	int typeBlock = AI::GetInstance()->GetBlock(position.x, position.y);
	if (typeBlock != BLOCK_GROUND)
		return false;

	return true;
}


int Node::GetIndexFromPosition() const
{
	return (int(m_vPosition.y) - 1)*(MAP_W - 2) + int(m_vPosition.x - 1);
}
