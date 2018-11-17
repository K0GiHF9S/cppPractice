#pragma once

class Caller
{
public:
	template<class F>
	inline void call(F func)
	{
		func();
	}

	inline Caller() = default;
	inline ~Caller() = default;
};

