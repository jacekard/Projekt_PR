#pragma once

#include <chrono>
using namespace std::chrono;

class Timer {
public:
	time_point<high_resolution_clock> now, temporary;
	milliseconds time;
	Timer() {};
	~Timer() {};
	void start() { 
		now = high_resolution_clock::now(); 
		temporary = now;
	}
	void end() { time = duration_cast<milliseconds>(high_resolution_clock::now() - now); }
	long long getResultMillis() { return time.count(); }
	double getResultSeconds() { return time.count()/1000.0; }
	long long getCycleMillis() { 
		long long millis = duration_cast<milliseconds>(high_resolution_clock::now() - temporary).count();
		temporary = high_resolution_clock::now();
		return millis;
	}
	double getCycleSeconds() { return duration_cast<milliseconds>(high_resolution_clock::now() - now).count() / 1000.0; }

};