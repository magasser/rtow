#pragma once

#include <chrono>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void Start()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		int64_t start =
			std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		int64_t end =
			std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Duration = end - start;
	}

	inline int64_t GetMicroseconds() const { return m_Duration; }
	inline double GetMilliseconds() const { return m_Duration * 0.001; }
	inline double GetSeconds() const { return GetMilliseconds() * 0.001; }

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	int64_t m_Duration = 0;
};
