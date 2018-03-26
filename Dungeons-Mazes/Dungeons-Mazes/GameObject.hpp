#pragma once
//#include "Config.hpp"
#include <string>
#include "UtilsConfig.hpp"

class GameObject {
public:
	Point m_Position;
	std::string m_Name;
	virtual void show() = 0;
	GameObject(Point p) : m_Position(p) {};
	~GameObject() {};
private:

};