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
	{
		uint64_t result = 0;
		uint64_t result2 = 0;

		::result = &result;
		::result2 = &result2;

		void (*func)(void) = add;
		Caller<decltype(func)> A(func);

		using namespace std::chrono;
		auto s = high_resolution_clock::now();
		for (int i = 0; i < MAX; ++i)
		{
			A.call();
			result2++;
		}
		auto e = high_resolution_clock::now();
		std::cout << result << std::endl;
		std::cout << duration_cast<microseconds>(e - s).count() << std::endl;
	}
	{
		uint64_t result = 0;
		uint64_t result2 = 0;

		::result = &result;
		::result2 = &result2;

		Caller<decltype(add)> A(add);

		using namespace std::chrono;
		auto s = high_resolution_clock::now();
		for (int i = 0; i < MAX; ++i)
		{
			A.call();
			result2++;
		}
		auto e = high_resolution_clock::now();
		std::cout << result << std::endl;
		std::cout << duration_cast<microseconds>(e - s).count() << std::endl;
	}
	{
		uint64_t result = 0;
		uint64_t result2 = 0;
		::result = &result;
		::result2 = &result2;
		auto f = [] {
			*::result += *::result2;
		};

		Caller<decltype(f)> A(f);
		using namespace std::chrono;
		auto s = high_resolution_clock::now();
		for (int i = 0; i < MAX; ++i)
		{
			A.call();
			result2++;
		}
		auto e = high_resolution_clock::now();
		std::cout << result << std::endl;
		std::cout << duration_cast<microseconds>(e - s).count() << std::endl;
	}

	{
		uint64_t result = 0;
		uint64_t result2 = 0;
		::result = &result;
		::result2 = &result2;
		auto f1 = [&result, &result2] {
			*::result += *::result2;
		};
		//std::function<void(void)> f = [&f1] {
		//	f1();
		//};

		//std::function<void(void)> f(std::ref(f1));
		std::function<void(void)> f([&result, &result2] {
			*::result += *::result2;
		});

		Caller<decltype(f)> A(f);
		using namespace std::chrono;
		auto s = high_resolution_clock::now();
		for (int i = 0; i < MAX; ++i)
		{
			A.call();
			result2++;
		}
		auto e = high_resolution_clock::now();
		std::cout << result << std::endl;
		std::cout << duration_cast<microseconds>(e - s).count() << std::endl;
	}

    return 0;
}


