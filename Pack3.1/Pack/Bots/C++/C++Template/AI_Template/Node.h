#pragma once
#include <glm/detail/type_vec2.hpp>
#include <vector>

const std::vector<glm::vec2> dirs = {glm::vec2(1,0),
									 glm::vec2(0,1),
									 glm::vec2(-1,0),
									 glm::vec2(0,-1)};

class Node
{
public:
	Node(glm::vec2 p, int type):m_vPosition(p),
								m_iType(type),
								m_fGscore(0),
								m_fHscore(0),
								m_pParrent(nullptr)
	{
	}

	~Node();

	glm::vec2 GetPosition() const;
	int Type() const;
	void UpdateGscore(float s);
	void UpdateHscore(float s);
	float GetGscore() const{ return m_fGscore; }
	float GetHscore() const{ return m_fHscore; }
	std::vector<glm::vec2> GetAdjacentNodePos() const;
	float GetPriority() const;
	bool operator<(const Node& right) const;
	bool isValidAdjacentPosition(glm::vec2 position) const;
	int GetIndexFromPosition() const;
	Node* GetParrent() const;
	void SetParrent(Node* p);
private:
	glm::vec2 m_vPosition;
	float m_fGscore;
	float m_fHscore;
	int m_iType;
	Node* m_pParrent;
};
