#pragma once
#define CENTER Point(0, 0)
#define UP Point(-1, 0)
#define DOWN Point(1, 0)
#define LEFT Point(0, -1)
#define RIGHT Point(0, 1)

class Point {
public:
	int x, y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
	Point(const Point& other) : x(other.x), y(other.y) {}
	inline void turnRight() {
		int tmp = x;
		x = y;
		y = -tmp;
	}
	friend bool operator== (const Point &p1, const Point &p2);
	friend bool operator!= (const Point &p1, const Point &p2);
	void operator= (const Point &other) {
		x = other.x;
		y = other.y;
	}
	Point operator+ (const Point &other)const {
		return Point(x + other.x, y + other.y);
	}
	Point operator- (const Point &other) const {
		return Point(x - other.x, y - other.y);
	}
	float getMoveWeight(const Point &p) {
		Point d = Point(x, y) - p;
		//sqrt(2) for oblique vector
		if (d.x * d.y > 0) return sqrt(2);
		//1 for cross vector
		else return 1.0;
	}
};

inline bool operator== (const Point &p1, const Point &p2) {
	return (p1.x == p2.x && p1.y == p2.y);
}

inline bool operator!= (const Point &p1, const Point &p2) {
	return !(p1.x == p2.x && p1.y == p2.y);
}

////////////////////////////////////////////////////////////
/// Function distance
/// @brief calculates distance from pitagorean algorithm
/// @in a, b - points to calculate distance between
////////////////////////////////////////////////////////////
inline float distance(Point a, Point b) {
	return sqrt(pow((a.x - b.x), 2) + pow(a.y - b.y, 2));
}

////////////////////////////////////////////////////////////
/// Function heuristic
/// @brief Euclidian distance between two points
/// @in a, b - points to calculate distance between
////////////////////////////////////////////////////////////
inline float heuristic(Point a, Point b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}