#pragma once

#include <chrono>
using namespace std::chrono;

class Timer {
public:
	time_point<high_resolution_clock> now;
	milliseconds time;
	Timer() {};
	~Timer() {};
	void start() { now = high_resolution_clock::now(); }
	void end() { time = duration_cast<milliseconds>(high_resolution_clock::now() - now); }
	long long getResultMillis() { return time.count(); }
	float getResultSeconds() { return time.count()/1000.0; }
	long long getMillisFromStart() { return duration_cast<milliseconds>(high_resolution_clock::now() - now).count(); }
	float getSecondsFromStart() { return duration_cast<milliseconds>(high_resolution_clock::now() - now).count() / 1000.0; }

};