#pragma once
#include <thread>
#include <mutex>
class RecurciveMutex
{
public:
	RecurciveMutex();
	~RecurciveMutex();
	void lock();
	bool try_lock();
	void unlock();
private:
	std::thread::id owner_;

};
