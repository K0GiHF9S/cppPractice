// templateMeta.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Wrapper.h"
#include <vector>
#include <map>
#include <iostream>
#include <queue>

struct Task
{
	int priority_;
	int member_;
	Task(int priority, int member) : priority_(priority), member_(member) {}
	~Task()
	{
		;
	}
};
using TaskPtr = std::shared_ptr<Task>;

auto less = [](const TaskPtr& lValue, const TaskPtr& rValue) {
	return (lValue->priority_ < rValue->priority_);
};

void Pop(std::priority_queue<TaskPtr, std::vector<TaskPtr>, decltype(less)>& q)
{
	if (!q.empty())
	{
		const auto elem = q.top();
		q.pop();
		std::cout << "priority:" << elem->priority_ << ",member:" << elem->member_ << std::endl;
	}
}

int main()
{
	std::priority_queue<TaskPtr, std::vector<TaskPtr>, decltype(less)> q(less);
	q.emplace(std::make_shared<Task>(0, 0));
	q.emplace(std::make_shared<Task>(0, 1));
	q.emplace(std::make_shared<Task>(2, 0));
	q.emplace(std::make_shared<Task>(1, 1));
	Pop(q);
	Pop(q);
	Pop(q);
	q.emplace(std::make_shared<Task>(2, 1));
	Pop(q);
	q.emplace(std::make_shared<Task>(0, 2));
	Pop(q);
	Pop(q);
	Pop(q);

	static_assert(IsTemplateOf<std::map<int, int>, std::map>::value, "only map or unordered_map");
	ref_type<int&> a;
	ref_type<std::shared_ptr<int>> b;
	//ValueType<std::vector<int>>::type c;
	static_assert(std::is_pointer_v<decltype(a)>, "");
	std::cout << typeid(a).name() << std::endl;
	std::cout << typeid(b).name() << std::endl;
    return 0;
}

