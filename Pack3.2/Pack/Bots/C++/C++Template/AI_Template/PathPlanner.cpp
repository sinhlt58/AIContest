#include "PathPlanner.h"
#include "AStarAlgorithm.h"


PathPlanner::PathPlanner(MyTank* owner)
{
	m_pOwner = owner;
}

bool PathPlanner::RequestPathToPosition(glm::vec2 target)
{
	//Astar here
	if (m_pOwner->GetPosition() == target)
		return false;

	m_Path = AStarAlgorithm::Search(m_pOwner->GetPosition(), target);
	return true;
}

PathPlanner::Path PathPlanner::GetPathAsEdges() const
{
	Path pathAsEdges;

	for (int i = 0; i < m_Path.size() - 1; i++)
	{
		pathAsEdges.push_back(PathEdge(glm::vec2(m_Path[i]),
									   glm::vec2(m_Path[i + 1]),
		                               PathEdge::normal_edge));
	}
	return pathAsEdges;
}

PathPlanner::~PathPlanner()
{
}
