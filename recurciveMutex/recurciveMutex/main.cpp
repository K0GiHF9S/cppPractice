#include "stdafx.h"

#include <iostream>
#include <thread>
#include <chrono>
#include "BusyMutex.h"
#include <mutex>
#include <condition_variable>

constexpr uint64_t N = 100000000;

int main()
{
	BusyMutex mtx;

	uint64_t n = 0;

	using namespace std::chrono;

	auto start = high_resolution_clock::now();

	auto lamda = [&]
	{
		for (uint64_t i = 0; i < N; i++)
		{
			std::condition_variable cond;
			std::lock_guard<BusyMutex> lk(mtx);
			n++;
		}
	};

	auto t1 = std::thread(lamda);
	auto t2 = std::thread(lamda);

	if (t1.joinable())
	{
		t1.join();
	}
	if (t2.joinable())
	{
		t2.join();
	}

	auto end = high_resolution_clock::now();
	std::cout << duration_cast<milliseconds>(end - start).count() << std::endl;
	std::cout << n << std::endl;

	return 0;
}
