#include "PathPlanner.h"
#include "AStarAlgorithm.h"
#include "HelperFunctions.h"


PathPlanner::PathPlanner(MyTank* owner)
{
	m_pOwner = owner;
}

bool PathPlanner::RequestPathToPosition(glm::vec2 target)
{
	//Astar here
//	std::cout << "Not round target: " << target.x << " " << target.y << std::endl;
	std::cout << "Rounded target: " << GetRoundPosition(target).x << " " << GetRoundPosition(target).y << std::endl;
	if (GetRoundPosition(m_pOwner->GetPosition()) == GetRoundPosition(target))
	{
		return false;
	}
		
	m_Path = AStarAlgorithm::Search(GetRoundPosition(m_pOwner->GetPosition()), GetRoundPosition(target),
		m_pOwner->ID(), -1);

	if (m_Path.size() < 2)
	{
		return false;
		std::cout << "size less than 2.\n";
	}
		

	std::cout << "After run A star.\n";
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
	if (m_pOwner->GetPosition() != pathAsEdges.front().Source())
	{
		glm::vec2 frontSource = pathAsEdges.front().Source();
		glm::vec2 frontDes= pathAsEdges.front().Destination();
		
		float minX, maxX;
		float minY, maxY;

		minX = frontSource.x < frontDes.x ? frontSource.x : frontDes.x;
		maxX = frontSource.x > frontDes.x ? frontSource.x : frontDes.x;
		minY = frontSource.y < frontDes.y ? frontSource.y : frontDes.y;
		maxY = frontSource.y > frontDes.y ? frontSource.y : frontDes.y;
		
		if (m_pOwner->GetPosition().x < maxX && m_pOwner->GetPosition().x > minX
		   || m_pOwner->GetPosition().y < maxY && m_pOwner->GetPosition().y > minY)
		{
			pathAsEdges.pop_front();
			pathAsEdges.push_front(PathEdge(m_pOwner->GetPosition(),
							       frontDes,
								   PathEdge::normal_edge));
			
		}else
		{
			pathAsEdges.push_front(PathEdge(m_pOwner->GetPosition(),
								   pathAsEdges.front().Source(),
								   PathEdge::normal_edge));
		}
	}
	return pathAsEdges;
}

PathPlanner::~PathPlanner()
{
}
