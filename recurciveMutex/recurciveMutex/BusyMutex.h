#pragma once

#include <atomic>
class BusyMutex
{
public:
	constexpr BusyMutex() noexcept = default;
	void lock() noexcept
	{
		while (mtx_.test_and_set());
	}
	bool try_lock() noexcept
	{
		return (mtx_.test_and_set());
	}
	void unlock() noexcept
	{
		mtx_.clear();
	}
private:
	std::atomic_flag mtx_ = ATOMIC_FLAG_INIT;
};
