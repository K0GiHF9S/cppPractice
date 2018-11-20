// readWriteLock.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "lockerTemplate.h"
#include <vector>


int main()
{
	lockerTemplate<std::vector<int>> vec;
	{
		const auto& read = vec.startRead();
		//read.obj_.push_back(1);
	}
	{
		auto write = vec.startWrite();
		write.obj_.push_back(1);
	}
    return 0;
}

