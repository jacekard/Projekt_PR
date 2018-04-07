#pragma once
#include "GameObject.hpp"
#include "Maze.hpp"

class Artifact : public GameObject {
public:
	void show() override;
	Artifact(Point p, string name, Maze* maze) : GameObject(p, maze) {};
	~Artifact();
};