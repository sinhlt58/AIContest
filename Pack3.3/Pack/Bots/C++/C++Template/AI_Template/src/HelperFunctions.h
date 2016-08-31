#pragma once
#include <glm/detail/type_vec2.hpp>
#include <cmath>

inline glm::vec2 GetRoundPosition(glm::vec2 p)
{
	return glm::vec2(round(p.x), round(p.y));
}
