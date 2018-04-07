#pragma once
#pragma once
#include "GameObject.hpp"

class AbstractPlayer : public GameObject {
public:
	virtual void move()=0;
	AbstractPlayer(Point p, string name, Maze* maze) : GameObject(p, maze) {
		m_pMaze = maze;
	};
	~AbstractPlayer();
};