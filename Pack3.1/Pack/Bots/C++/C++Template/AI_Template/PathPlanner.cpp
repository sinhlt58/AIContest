#include "PathPlanner.h"


PathPlanner::PathPlanner(MyTank* owner)
{
	m_pOwner = owner;
}

bool PathPlanner::RequestPathToPosition(glm::vec2 target) const
{
	//Astar here

	return false;
}

PathPlanner::Path PathPlanner::GetPath()
{
	Path path;
	return path;
}

std::vector<glm::vec2> PathPlanner::AStarSearch(glm::vec2 start, glm::vec2 goal)
{
	std::vector<glm::vec2> a;
	return a;
}

PathPlanner::~PathPlanner()
{
}
