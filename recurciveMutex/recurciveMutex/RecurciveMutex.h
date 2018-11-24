#pragma once
#include <thread>
#include <mutex>
#include <atomic>
#include "BusyMutex.h"
class RecurciveMutex
{
public:
	inline RecurciveMutex() noexcept = default;
	inline ~RecurciveMutex() noexcept = default;
	inline void lock() noexcept
	{
		const auto& own = std::this_thread::get_id();
		if (owner_.load(std::memory_order_relaxed) != own)
		{
			mtx_.lock();
			owner_.store(own, std::memory_order_relaxed);
		}
		++count_;
	}

	inline bool try_lock() noexcept
	{
		const auto& own = std::this_thread::get_id();
		if (owner_.load(std::memory_order_relaxed) != own)
		{
			if (!mtx_.try_lock())
			{
				return (false);
			}
			owner_.store(own, std::memory_order_relaxed);
		}
		++count_;
		return (true);
	}

	inline void unlock() noexcept
	{
		const auto& own = std::this_thread::get_id();
		if (owner_.load(std::memory_order_relaxed) != own)
		{
			return;
		}
		if (--count_ <= 0)
		{
			owner_.store(std::thread::id(), std::memory_order_relaxed);
			mtx_.unlock();
		}
	}

private:
	std::atomic<std::thread::id> owner_;
	unsigned int count_ = 0;
	BusyMutex mtx_;
};
