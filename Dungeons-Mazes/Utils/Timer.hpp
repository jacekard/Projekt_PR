#pragma once

#include <chrono>
#include <numeric>
using namespace std::chrono;

class Timer {
public:
	time_point<high_resolution_clock> now, cycle;
	vector<double> cyclesDuration;
	pair<double, double> time;

	Timer() {
		time = std::make_pair(0, 0);
	};
	~Timer() {};
	void start() { 
		now = high_resolution_clock::now(); 
	}
	double end() { return duration_cast<milliseconds>(high_resolution_clock::now() - now).count(); }

	void tick() {
		cycle = high_resolution_clock::now();
	}
	double tock() { 
		double millis = duration_cast<milliseconds>(high_resolution_clock::now() - cycle).count();
		cyclesDuration.push_back(millis);
		return millis;
	}
	void countCyclesDuration() {
		if (cyclesDuration.size() == 0)
			time.first = 0;
		else time.first = (double)std::accumulate(cyclesDuration.begin(),
			cyclesDuration.end(), 0.0);
	}
	void countCyclesAverage() {
		if (cyclesDuration.size() == 0)
			time.second = 0;
		else time.second = (double)std::accumulate(cyclesDuration.begin(),
			cyclesDuration.end(), 0.0) / cyclesDuration.size();
	}
	void countResults() {
		countCyclesDuration();
		countCyclesAverage();
	}
};