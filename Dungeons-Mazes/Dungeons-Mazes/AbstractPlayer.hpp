#pragma once
#include "GameObject.hpp"
#include "Timer.hpp"

class AbstractPlayer : public GameObject {
public:
	string m_Name;
	Timer m_Timer;
	bool m_hasMoved;
	int m_ArtifactsObtained;

	AbstractPlayer(Point p, string name, Maze* maze) : GameObject(p, maze) {
		m_Name = name;
		m_Timer = Timer();
		m_hasMoved = false;
		m_ArtifactsObtained = 0;
	};

	~AbstractPlayer() {};
	virtual void move() = 0;
	friend ostream& operator<< (ostream& os, const AbstractPlayer& pl);
};