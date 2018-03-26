#pragma once
#pragma once
#include "Config.hpp"

class AbstractPlayer : public GameObject {
public:
	string m_Name;
	Maze* m_pMaze;
	virtual void show();
	virtual void move();
	AbstractPlayer(Point p, string name, Maze* maze) : GameObject(p) {
		m_Name = name;
		m_pMaze = maze;
	};
	~AbstractPlayer();
};