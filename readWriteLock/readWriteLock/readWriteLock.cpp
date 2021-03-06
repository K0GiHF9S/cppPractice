// readWriteLock.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "lockerTemplate.h"
#include <vector>

constexpr int N = 1000000;

int main()
{
	lockerTemplate<std::vector<int>> vec;
	std::thread a1([&]{
		for (int i = 0; i < N; i++)
		{
			auto write = vec.startWrite();
			write.obj_.push_back(i);
		}
	});
	std::thread a2([&] {
		for (int i = 0; i < N; i++)
		{
			auto write = vec.startWrite();
			write.obj_.push_back(i);
		}
	});
	std::thread b1([&] {
		for (int i = 0; i < N; i++)
		{
			const auto& read = vec.startRead();
			for (auto elem : read.obj_)
			{
				auto a = elem;
			}
		}
	});
	std::thread b2([&] {
		for (int i = 0; i < N; i++)
		{
			const auto& read = vec.startRead();
			for (auto elem : read.obj_)
			{
				auto a = elem;
			}
		}
	});
	a1.join();
	a2.join();
	b1.join();
	b2.join();
    return 0;
}

