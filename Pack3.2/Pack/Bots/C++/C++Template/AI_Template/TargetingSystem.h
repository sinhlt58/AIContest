#pragma once
#include "MyTank.h"

class MyTank;

class TargetingSystem
{
public:
	TargetingSystem(MyTank* pOwner);
	~TargetingSystem();

	void Update();

	bool isTargetingEnemyPresent();
	bool isTargetingEnemyShootable();
	glm::vec2 GetTargetingEnemyPosition();
	int GetAimDirection();
private:
	MyTank* m_pOwner;
	int m_iTargetEnemyId;
};

