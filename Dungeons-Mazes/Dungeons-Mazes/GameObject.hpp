#pragma once
//#include "Config.hpp"
#include <string>
#include "UtilsConfig.hpp"


class Maze;
class GameObject {
public:
	Maze * m_pMaze;
	Point m_Position;
	std::string m_Name;
	virtual void show() = 0;
	GameObject(Point p, Maze* m) : m_Position(p), m_pMaze(m) {};
	~GameObject() {};
private:

};