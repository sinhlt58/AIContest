#pragma once
#include "include/ai/defines.h"
#include "Node.h"

const int numNodes = (MAP_W - 2)*(MAP_H - 2);
const int noParrent = -1;

class AStarAlgorithm
{
private:
//	bool isVisited(Node &node) const;
//	bool isInFrontier(Node &node) const;
	float Manhattan(glm::vec2& p1, glm::vec2& p2) const;
	void IndexToPosition(int index, int &x, int &y);
public:
	AStarAlgorithm();
	~AStarAlgorithm();
	std::vector<glm::vec2> Search(glm::vec2 start, glm::vec2 goal);
};

