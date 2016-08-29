#include "AStarAlgorithm.h"
#include <queue>
#include <iostream>
#include <set>
#include "Globals.h"

AStarAlgorithm::AStarAlgorithm()
{

}


AStarAlgorithm::~AStarAlgorithm()
{
}


std::vector<glm::vec2> AStarAlgorithm::Search(glm::vec2 start, glm::vec2 goal, int currentTankId, int targetTankId)
{
	bool closedNodes[numNodes] = { false };
	float openNodes[numNodes] = { 0 };
//	std::priority_queue<Node> pq;
	std::multiset<Node> prioritySet;
	
	int cameFrom[numNodes] = {noParrent};

	std::vector<glm::vec2> path;

	Node* node;
	node = new Node(start, BLOCK_GROUND);
	node->UpdateHscore(Manhattan(start, goal));
//	pq.push(*node);
	prioritySet.insert(*node);
	closedNodes[node->GetIndexFromPosition()] = true;
	openNodes[node->GetIndexFromPosition()] = node->GetPriority();

	while(!prioritySet.empty())
	{
//		node = new Node(pq.top().GetPosition(), pq.top().Type());
//		pq.pop();
		auto first = prioritySet.begin();
		node = new Node(first->GetPosition(), first->Type());
		prioritySet.erase(first);
		openNodes[node->GetIndexFromPosition()] = 0;
		closedNodes[node->GetIndexFromPosition()] = true;

		if (node->GetPosition() == goal || prioritySet.size() >= 21)
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
//			while(!pq.empty())
//			{
//				pq.pop();
//			}
			while(!prioritySet.empty())
			{
				auto it = prioritySet.begin();
				prioritySet.erase(it);
			}
			delete node;
			return path;
		}
		
		for (glm::vec2 ajPos :  node->GetAdjacentNodePos(currentTankId, targetTankId, goal))
		{
			Node* child = new Node(ajPos, BLOCK_GROUND);
			child->UpdateGscore(node->GetGscore() + 1);
			child->UpdateHscore(Manhattan(ajPos, goal));
			if (closedNodes[child->GetIndexFromPosition()] == false)
			{	
//				pq.push(*child);
				if (openNodes[child->GetIndexFromPosition()] == 0)
				{	
					openNodes[child->GetIndexFromPosition()] = child->GetPriority();
					cameFrom[child->GetIndexFromPosition()] = node->GetIndexFromPosition();
					prioritySet.insert(*child);
				}else if(openNodes[child->GetIndexFromPosition()] > child->GetPriority())
				{
					auto it = prioritySet.begin();
					for (it; it != prioritySet.end(); ++it)
					{
						if (it->GetPosition() == child->GetPosition())
							break;
					}
					prioritySet.erase(it);
					openNodes[child->GetIndexFromPosition()] = child->GetPriority();
					cameFrom[child->GetIndexFromPosition()] = node->GetIndexFromPosition();
					prioritySet.insert(*child);
				}else
				{
					delete child;
				}
			}
		}
		delete node;
	}

	return path;
}

void AStarAlgorithm::IndexToPosition(int index, int& x, int& y)
{
	x = index % (MAP_W - 2) + 1;
	y = index / (MAP_W - 2) + 1;
}
