#pragma once
#include "Config.hpp"

class Bot : public GameObject {
public:
	Bot(Point p) : GameObject(p) {};
	~Bot();
	void show() override {};
};