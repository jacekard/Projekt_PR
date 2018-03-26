#pragma once
#include "AbstractPlayer.hpp"

class Player : public AbstractPlayer {
public:
	void show() override;
	void move();
	Player(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {};
	~Player();
};