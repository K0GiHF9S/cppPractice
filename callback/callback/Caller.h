#pragma once

template<class F>
class Caller
{
private:
	F& func_;
public:
	inline void call()
	{
		func_();
	}

	inline Caller(F& func) : func_(func) {};
	inline ~Caller() = default;
};

