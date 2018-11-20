// templateMeta.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Wrapper.h"
#include <vector>
#include <map>
#include <stdio.h>

int main()
{
	static_assert(IsTemplateOf<std::map<int, int>, std::map>::value, "only map or unordered_map");
	constexpr bool x = IsMapOf<std::vector<int>>();
	printf("%d\n", x);
    return 0;
}

