#pragma once
#include "MyTank.h"

class MyTank;

class SteeringBehavior
{
public:
	SteeringBehavior(MyTank* owner): m_pOwner(owner),
	                                 m_iFlags(0)
	{
	};

	~SteeringBehavior();

	//Return a direction. LEFT, RIGHT, UP, DOWN.
	int Calculate() const;

	void SeekOn()
	{
		m_iFlags |= seek;
	}

	void SeekOff()
	{
		if (On(seek)) m_iFlags = m_iFlags & ~seek;
	}

	void SetTarget(glm::vec2 target);
	glm::vec2 m_vTarget;
private:
	enum behavior_type
	{
		none = 0,
		seek = 1 << 0
	};

	MyTank* m_pOwner;

	int m_iFlags;

	bool On(behavior_type bt) const
	{
		return (m_iFlags & bt) == bt;
	}

	//Return a direction.
	int Seek(glm::vec2 target) const;
};
