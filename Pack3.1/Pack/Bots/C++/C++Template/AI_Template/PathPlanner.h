#pragma once
#include "MyTank.h"
#include <list>
#include "PathEdge.h"
#include <vector>

class MyTank;
class PathEdge;

class PathPlanner
{
private:
	enum { no_closest_node_found = -1};
public:
	PathPlanner(MyTank* owner);
	~PathPlanner();
	typedef std::list<PathEdge> Path;
	                  private:
	                  MyTank* m_pOwner;
	glm::vec2 m_vDestinationPos;
	bool RequestPathToPosition(glm::vec2 target) const;
	Path GetPath();
	std::vector<glm::vec2> AStarSearch(glm::vec2 start, glm::vec2 goal);
};

