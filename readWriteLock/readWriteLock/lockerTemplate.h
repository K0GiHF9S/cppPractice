#pragma once

#include <shared_mutex>

template <class T>
class readLockedObject
{
public:
	readLockedObject(std::shared_mutex& mutex, const T& obj) : obj_(obj), lk_(mutex)
	{
		;
	}

	~readLockedObject()
	{
		;
	}

	readLockedObject& operator=(readLockedObject&& u) noexcept = default;
	readLockedObject(readLockedObject&& u) noexcept = default;

	const T& obj_;

private:
	std::shared_lock<std::shared_mutex> lk_;
};

template <class T>
class writeLockedObject
{
public:
	writeLockedObject(std::shared_mutex& mutex, T& obj) : obj_(obj), lk_(mutex)
	{
		;
	}

	~writeLockedObject()
	{
		;
	}

	writeLockedObject& operator=(writeLockedObject&& u) noexcept = default;
	writeLockedObject(writeLockedObject&& u) noexcept = default;

	T& obj_;

private:
	std::unique_lock<std::shared_mutex> lk_;
};

template <class T>
class lockerTemplate
{
public:
	readLockedObject<T> startRead() const
	{
		return (readLockedObject<T> (mutex_, obj_));
	}

	writeLockedObject<T> startWrite()
	{
		return (writeLockedObject<T>(mutex_, obj_));
	}

private:
	mutable std::shared_mutex mutex_;
	T obj_;
};
