#include "stdafx.h"

#include <iostream>
#include <thread>
#include <chrono>
#include "RecurciveMutex.h"
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <Windows.h>

constexpr uint64_t L = 10000;
constexpr uint64_t N = 100000;
constexpr uint64_t M = 10;

int main()
{
	using Mutex = RecurciveMutex;
	Mutex mtx;

	for (int j = 0; j < L; j++)
	{
		uint64_t n = 0;

		using namespace std::chrono;

		auto start = high_resolution_clock::now();

		auto lamda = [&]
		{
			for (uint64_t i = 0; i < N; i++)
			{
				std::lock_guard<Mutex> lk(mtx);
				n++;
			}
		};

		std::vector<std::thread> vec(M);
		for (auto& v : vec)
		{
			v = std::thread(lamda);
		}

		for (int i = 0; i < M - 1; i++)
		{
			std::lock_guard<Mutex> lk(mtx);
			::TerminateThread(vec[i].native_handle(), 0);
			if (vec[i].joinable())
			{
				vec[i].detach();
			}
		}
		if (vec[M - 1].joinable())
			vec[M - 1].join();

		auto end = high_resolution_clock::now();
		std::cout << duration_cast<milliseconds>(end - start).count() << std::endl;
		std::cout << n << std::endl;
	}
	return 0;
}
