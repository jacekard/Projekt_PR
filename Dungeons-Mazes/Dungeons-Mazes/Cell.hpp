#pragma once
#include "Config.hpp"

class Cell : public GameObject {
private:
	vector<Cell> m_Neighbors;
	bool m_IsWall;
public:	
	Cell(Point p);
	~Cell();
	void show() override;
};