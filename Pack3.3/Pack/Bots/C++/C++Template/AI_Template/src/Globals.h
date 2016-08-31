#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "ai/defines.h"

class Globals
{
public:
	static int s_TotalLoops;

	static int GetLoopCount()
	{
		return s_TotalLoops;
	}
};

const std::vector<glm::vec2> dirs = {glm::vec2(1, 0),
									 glm::vec2(0, 1),
									 glm::vec2(-1, 0),
									 glm::vec2(0, -1)};

inline float Manhattan(glm::vec2 p1, glm::vec2 p2)
{
	return abs(p1.x - p2.x) +
		abs(p1.y - p2.y);
}

const int numNodes = (MAP_W - 2)*(MAP_H - 2);
const int noParrent = -1;