#pragma once
//#include "Config.hpp"
#include <string>
#include "UtilsConfig.hpp"

class GameObject {
protected:
	Point m_Position;
	//Maze m_Maze;
public:
	std::string m_Name;
	virtual void show() = 0;
	GameObject(Point p) : m_Position(p) {};
	~GameObject() {};
private:

};