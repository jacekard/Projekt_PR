#pragma once

class Point {
public:
	int x, y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

inline int distance(Point a, Point b) {
	return sqrt(pow((a.x - b.x), 2) + pow(a.y - b.y, 2));
}

inline int heuristic(Point a, Point b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}