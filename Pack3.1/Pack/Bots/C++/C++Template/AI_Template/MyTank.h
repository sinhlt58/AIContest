#pragma once
#include "include/ai/Tank.h"
#include "glm/vec2.hpp"
#include "SteeringBehavior.h"

class Tank;
class SteeringBehavior;

class MyTank
{
public:
	MyTank(int id);
	~MyTank();
	
	void Update();
	void UpdateMovement();

	Tank* GetApiTank() const;

	glm::vec2 GetPosition() const;
	SteeringBehavior* GetSteering() const;
private:
	int m_iId;

	//Steering behavior.
	SteeringBehavior* m_pSteeringBehavior;

	//Brain.

	//Target system.
};

