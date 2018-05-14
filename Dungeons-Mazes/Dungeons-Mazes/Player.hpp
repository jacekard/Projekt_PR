#pragma once
#include "AbstractPlayer.hpp"

class Player : public AbstractPlayer {
public:
	Point m_Direction;
	void checkInputStatus();
	void show() override;
	void move();
	Player(Point, PlayerType, Maze*);
	~Player();
};