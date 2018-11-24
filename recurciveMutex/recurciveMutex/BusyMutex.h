#pragma once

#include <atomic>
class BusyMutex
{
public:
	inline constexpr BusyMutex() noexcept = default;
	inline ~BusyMutex() noexcept = default;
	inline void lock() noexcept
	{
		while (mtx_.test_and_set(std::memory_order_relaxed));
	}
	inline bool try_lock() noexcept
	{
		return (mtx_.test_and_set(std::memory_order_relaxed));
	}
	inline void unlock() noexcept
	{
		mtx_.clear(std::memory_order_relaxed);
	}
private:
	std::atomic_flag mtx_ = ATOMIC_FLAG_INIT;
};
