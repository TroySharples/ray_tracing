#pragma once
#include <chrono>
#include <string>
#include <iostream>

class timer
{
public:
	timer(std::string str)
	{
		start_time = std::chrono::time_point<std::chrono::high_resolution_clock>.now();
		std::cout
			<< str
			<< " -> "
			<< "Timer started...\n"
	}

	~timer()
	{
		end_time = std::chrono::time_point<std::chrono::high_resolution_clock>.now();
		std::chrono::time_point<std::chrono::high_resolution_clock> duration = end_time - start_time;
		std::cout
			<< str
			<< " -> "
			<< "Timer finished."
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
	std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};