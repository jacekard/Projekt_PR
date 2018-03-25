#pragma once
#include "GameObject.hpp"

class Player : public GameObject {
public:
	virtual void show();
	void move();
	Player(Point p) : GameObject(p) {};
	~Player();
};