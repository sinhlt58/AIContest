#include "AStarAlgorithm.h"
#include <queue>
#include <iostream>

AStarAlgorithm::AStarAlgorithm()
{

}


AStarAlgorithm::~AStarAlgorithm()
{
}


std::vector<glm::vec2> AStarAlgorithm::Search(glm::vec2 start, glm::vec2 goal)
{
	bool closedNodes[numNodes] = { false };
	float openNodes[numNodes] = { 0 };
	std::priority_queue<Node> pq;
	int cameFrom[numNodes] = {noParrent};

	std::vector<glm::vec2> path;

	Node* node;
	node = new Node(start, BLOCK_GROUND);
	node->UpdateHscore(Manhattan(start, goal));
	pq.push(*node);
	closedNodes[node->GetIndexFromPosition()] = true;
	openNodes[node->GetIndexFromPosition()] = node->GetPriority();

	while(!pq.empty())
	{
		node = new Node(pq.top().GetPosition(), pq.top().Type());
		pq.pop();
		openNodes[node->GetIndexFromPosition()] = 0;
		closedNodes[node->GetIndexFromPosition()] = true;

		if (node->GetPosition() == goal)
		{
//			Node* run = node;
//			std::cout << node->GetPosition().x << " " << node->GetPosition().y << std::endl;
//			while(run->GetParrent() != nullptr)
//			{
//				std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAaa";
//				std::cout << run->GetPosition().x << " " << run->GetPosition().y << std::endl;
//				run = run->GetParrent();
//			}
			int index = node->GetIndexFromPosition();
			while(cameFrom[index] != noParrent)
			{
				index = cameFrom[index];
				int x, y;
				IndexToPosition(index, x, y);
				std::cout << x << " " << y << std::endl;
			}
			return path;
		}

		for (glm::vec2 ajPos :  node->GetAdjacentNodePos())
		{
			
			Node* child = new Node(ajPos, BLOCK_GROUND);
			if (closedNodes[child->GetIndexFromPosition()] == false)
			{	
//				child->SetParrent(node);
				cameFrom[child->GetIndexFromPosition()] = node->GetIndexFromPosition();
				child->UpdateGscore(node->GetGscore() + 1);
				child->UpdateHscore(Manhattan(ajPos, goal));
				pq.push(*child);
			}else
			{
				delete child;
			}
		}
	}

	return path;
}

//bool AStarAlgorithm::isVisited(Node& node) const
//{
//	return m_ClosedNodes[node.GetIndexFromPosition()] != nullptr;
//}
//
//bool AStarAlgorithm::isInFrontier(Node& node) const
//{
//	return m_OpenNodes[node.GetIndexFromPosition()] > 0;
//}


float AStarAlgorithm::Manhattan(glm::vec2& p1, glm::vec2& p2) const
{
	return abs(p1.x - p2.x) + 
		   abs(p1.y - p2.y);
}

void AStarAlgorithm::IndexToPosition(int index, int& x, int& y)
{
	x = index % (MAP_W - 2) + 1;
	y = index / (MAP_W - 2) + 1;
}
