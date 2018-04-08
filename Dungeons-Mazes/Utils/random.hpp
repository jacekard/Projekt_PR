#pragma once
#include <random>
using namespace std;

inline float random() {
	//random number between 0 and 1
	random_device rd;
	uniform_real_distribution<float> dist(0.0, 1.0);
	return dist(rd);
}

inline int random(int a) {
	//random number between 0 and a
	random_device rd;
	uniform_int_distribution<int> dist(0, a);
	return dist(rd);
}



inline int random(int a, int b) {
	//random number between a and b
	random_device rd;
	uniform_int_distribution<int> dist(a, b);
	return dist(rd);
}

inline float random(float a) {
	//random number between 0 and a
	random_device rd;
	uniform_real_distribution<float> dist(0, a);
	return dist(rd);
}

inline float random(float a, float b) {
	//random number between a and b
	random_device rd;
	uniform_real_distribution<float> dist(a, b);
	return dist(rd);
}