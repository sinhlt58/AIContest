#include "SteeringBehavior.h"
#include "glm/glm.hpp"
#include <iostream>

SteeringBehavior::~SteeringBehavior()
{
}

int SteeringBehavior::Calculate() const
{
//	return DIRECTION_UP;
	if(On(seek))
	{
		return Seek(m_vTarget);
	}
	return DIRECTION_NONE;
}

void SteeringBehavior::SetTarget(glm::vec2 target)
{
	m_vTarget = target;
}

int SteeringBehavior::Seek(glm::vec2 target) const
{
	glm::vec2 tankPosition = m_pOwner->GetPosition();
//	std::cout << "My tank: "<< tankPosition.x << " " << tankPosition.y << std::endl;
	glm::vec2 direction = target - tankPosition;

	if (direction.length())
	{
		direction = glm::normalize(direction);
		if (direction.y == 0)
		{
			if (direction.x > 0)
				return DIRECTION_RIGHT;
			return DIRECTION_LEFT;
		}
		if (direction.x == 0)
		{
			if (direction.y > 0)
				return DIRECTION_DOWN;
			return DIRECTION_UP;
		}
		//both x > 0 and y > 0, will go horizontally.
		if (direction.x > 0)
			return DIRECTION_RIGHT;
		return DIRECTION_LEFT;
	}
	
	return DIRECTION_NONE;
}