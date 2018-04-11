#pragma once
#include "GameObject.hpp"
#include "Timer.hpp"

class AbstractPlayer : public GameObject {
public:
	string m_Name;
	Timer m_timer;
	bool m_hasMoved;

	AbstractPlayer(Point p, string name, Maze* maze) : GameObject(p, maze) {
		m_Name = name;
		m_timer = Timer();
		m_hasMoved = false;
	};
	~AbstractPlayer() {};
	virtual void move() = 0;
};