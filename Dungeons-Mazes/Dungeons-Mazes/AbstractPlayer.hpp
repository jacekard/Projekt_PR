#pragma once
#include "GameObject.hpp"

class AbstractPlayer : public GameObject {
public:
	string m_Name;
	virtual void move()=0;

	AbstractPlayer(Point p, string name, Maze* maze) : GameObject(p, maze) {
		m_Name = name;
	};

	~AbstractPlayer() {};
};