#pragma once
#include "GameObject.hpp"
#include "Timer.hpp"

enum PlayerType {
	ASTAR,
	DIJKSTRA,
	PLEDGE,
	PLAYER,
	NONE
};

class AbstractPlayer : public GameObject {
public:
	string m_Name;
	Timer m_Timer;
	PlayerType m_PlayerType;
	bool m_hasMoved;
	int m_ArtifactsObtained;

	AbstractPlayer(Point p, PlayerType playerType, Maze* maze) : GameObject(p, maze) {
		m_PlayerType = playerType;
		m_Timer = Timer();
		m_hasMoved = false;
		m_ArtifactsObtained = 0;
	};

	~AbstractPlayer() {};
	virtual void move() = 0;
	string enumToString(PlayerType) const;
	friend ostream& operator<< (ostream& os, const AbstractPlayer& pl);
};