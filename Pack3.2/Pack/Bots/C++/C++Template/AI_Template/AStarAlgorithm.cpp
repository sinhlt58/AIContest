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
			int x, y;
			int index = node->GetIndexFromPosition();
			while(cameFrom[index] != noParrent)
			{
				IndexToPosition(index, x, y);
//				std::cout << x << " " << y << std::endl;
				auto it = path.begin();
				path.insert(it, glm::vec2(x, y));
				index = cameFrom[index];
			}
			while(!pq.empty())
			{
				pq.pop();
			}
			return path;
		}

		for (glm::vec2 ajPos :  node->GetAdjacentNodePos())
		{		
			Node* child = new Node(ajPos, BLOCK_GROUND);
			if (closedNodes[child->GetIndexFromPosition()] == false
				|| openNodes[child->GetIndexFromPosition()] > child->GetPriority())
			{	
				openNodes[child->GetIndexFromPosition()] = child->GetPriority();
				cameFrom[child->GetIndexFromPosition()] = node->GetIndexFromPosition();
				child->UpdateGscore(node->GetGscore() + 1);
				child->UpdateHscore(Manhattan(ajPos, goal));
				pq.push(*child);
			}else
			{
				delete child;
			}
		}
		delete node;
	}

	return path;
}

float AStarAlgorithm::Manhattan(glm::vec2 p1, glm::vec2 p2)
{
	return abs(p1.x - p2.x) + 
		   abs(p1.y - p2.y);
}

void AStarAlgorithm::IndexToPosition(int index, int& x, int& y)
{
	x = index % (MAP_W - 2) + 1;
	y = index / (MAP_W - 2) + 1;
}
