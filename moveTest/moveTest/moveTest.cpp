// moveTest.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <atomic>
#include <mutex>
#include <map>
#include <vector>
#include <memory>
#include <shared_mutex>

struct A
{
	std::map<int, int> a;
	int& b;
	int c;
	A(int& a) : b(a) {}

	//A& operator=(const A& r)
	//{
	//	;
	//}
	A& operator=(const A&) = delete;

	//A(const A&)
	//{
	//	;
	//}
	A(const A&) = delete;

	//A& operator=(A&& r) noexcept
	//{
	//	a = std::move(r.a);
	//	b = std::move(r.b);
	//	c = std::move(r.c);
	//	return (*this);
	//}
	A& operator=(A&& r) noexcept = delete;

	A(A&& r) noexcept :
		a(std::move(r.a)),
		b(r.b),
		c(r.c)
	{
	}
};

template <class T>
class UnlockedObject {
public:
	UnlockedObject(T& Obj, std::mutex& mtx) : Obj_(Obj), lk_(mtx_) {};
	T& Obj_;
private:
	std::lock_guard<std::mutex> lk_;
};

template <class T>
class LockedObject {
public:
	LockedObject(std::mutex& mtx) : mtx_(mtx) {}
	UnlockedObject GetToken(void)
	{
		std::defer_lock_t a;
		return();
	}

private:
	std::mutex& mtx_;
	T Obj_;
};

int main()
{
	int n = 0;
	A a(n);
	int m = 0;
	A b = std::move(a);
	//b = std::move(a);
	n = 1;



	return 0;
}

