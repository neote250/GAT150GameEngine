#pragma once
#include <chrono>

class Time {
private:
	using clock = std::chrono::high_resolution_clock;

public:
	Time() : 
		_startTime{ clock::now() }
		, _frameTime{clock::now()} 
	{}

	void Tick();
	void Reset() { _startTime = clock::now(); }

	float GetTime() const { return _time; }
	float GetDeltaTime() const { return _deltaTime; }



private:
	float _time{ 0 };
	float _deltaTime{ 0 };

	clock::time_point _startTime;
	clock::time_point _frameTime;
};
