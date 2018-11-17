#include "stdafx.h"
#include "caller.h"
#include <limits>
#include <chrono>
#include <iostream>
#include <functional>

//constexpr int MAX = 1000;
constexpr int MAX = std::numeric_limits<int>::max();

uint64_t* result;
uint64_t* result2;
void add()
{
	*result += *result2;
}

int main()
{
	Caller A;


	{
		uint64_t result = 0;
		uint64_t result2 = 0;

		::result = &result;
		::result2 = &result2;

		using namespace std::chrono;
		auto s = high_resolution_clock::now();
		for (int i = 0; i < MAX; ++i)
		{
			A.call(add);
			result2++;
		}
		auto e = high_resolution_clock::now();
		std::cout << result << std::endl;
		std::cout << duration_cast<microseconds>(e - s).count() << std::endl;
	}
	{
		uint64_t result = 0;
		uint64_t result2 = 0;
		auto f = [&result, &result2] {
			result += result2;
		};

		using namespace std::chrono;
		auto s = high_resolution_clock::now();
		for (int i = 0; i < MAX; ++i)
		{
			A.call(f);
			result2++;
		}
		auto e = high_resolution_clock::now();
		std::cout << result << std::endl;
		std::cout << duration_cast<microseconds>(e - s).count() << std::endl;
	}

	{
		uint64_t result = 0;
		uint64_t result2 = 0;
		std::function<void(void)> f = [&result, &result2] {
			result += result2;
		};

		using namespace std::chrono;
		auto s = high_resolution_clock::now();
		for (int i = 0; i < MAX; ++i)
		{
			A.call(f);
			result2++;
		}
		auto e = high_resolution_clock::now();
		std::cout << result << std::endl;
		std::cout << duration_cast<microseconds>(e - s).count() << std::endl;
	}

    return 0;
}


