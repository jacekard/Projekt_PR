#pragma once
#include "GameObject.hpp"
#include "Timer.hpp"

class AbstractPlayer : public GameObject {
public:
	string m_Name;
	Timer timer;
	bool hasMoved;

	AbstractPlayer(Point p, string name, Maze* maze) : GameObject(p, maze) {
		m_Name = name;
		timer = Timer();
		hasMoved = false;
	};
	~AbstractPlayer() {};
	virtual void move() = 0;
};