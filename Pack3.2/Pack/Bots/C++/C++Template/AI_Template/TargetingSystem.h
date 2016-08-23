#pragma once
#include "MyTank.h"

class MyTank;

class TargetingSystem
{
public:
	TargetingSystem(MyTank* pOwner);
	~TargetingSystem();

	void Update();
private:
	MyTank* m_pOwner;
	glm::vec2 m_vCurrentTarget;
};

