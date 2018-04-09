#pragma once
#define NOP Point(0, 0)
#define UP Point(-1, 0)
#define DOWN Point(1, 0)
#define LEFT Point(0, -1)
#define RIGHT Point(0, 1)
class Point {
public:
	int x, y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
	friend bool operator== (const Point &p1, const Point &p2);
	friend bool operator!= (const Point &p1, const Point &p2);
	void operator= (const Point &other) {
		x = other.x;
		y = other.y;
	}
};

inline bool operator== (const Point &p1, const Point &p2) {
	return (p1.x == p2.x && p1.y == p2.y);
}

inline bool operator!= (const Point &p1, const Point &p2) {
	return !(p1.x == p2.x && p1.y == p2.y);
}

inline double distance(Point a, Point b) {
	return sqrt(pow((a.x - b.x), 2) + pow(a.y - b.y, 2));
}

inline double heuristic(Point a, Point b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}