#pragma once

#include <stack>

namespace util {

	inline int flip(int n) {
		return n ^ 1;
	}

	inline int sign(int n) {
		return flip((n >> 31) & 1);
	}

	inline int getmax(int a, int b) {
		int c = a - b;
		int sa = sign(a);
		int sb = sign(b);
		int sc = sign(c);
		int diffsab = sa ^ sb;
		int samesab = flip(diffsab);

		//
		int returnA = diffsab * sa + samesab * sc;
		int returnB = flip(returnA);
		return a * returnA + b * returnB;
	}

	template<class T>
	inline T add(T a, T b)
	{
		T sum = a;
		while (b != 0)
		{
			sum = a ^ b;
			b = (a&b) << 1;
			a = sum;
		}
		return sum;
	}

	template<class T, size_t N>
	inline std::array<T, N>&& add(std::array<T, N> a, std::array<T, N>b)
	{
		std::array<T, N> sum = a;
		for (int i = 0; i < sizeof(T)*N; ++i)
		{
			//TODO
			//sum = a.data() ^ b.data();
			//b = ()
		}
	}

	inline char* stacktocharp(std::stack<char>& sc)
	{

	}

	std::stack<char>& xor(const char* a, const char* b)
	{
		const char* pa = a;
		const char* pb = b;
		while (*pa) 
			++pa;
		while (*pb)
			++pb;
		std::stack<char> result;
		for (--pa, --pb;pa != a && pb != b;--pa,--pb) {
			result.push(*pa^*pb);
		}
		result.push(*pa^*pb);

		if (pa == a && pb == b)
		{
			//pass
		}
		else if (pa == a) //pa is short one
		{
			for (--pb;pb != b; --pb)
			{
				result.push(*pb);
			}
			result.push(*pb);
		}
		else if (pb == b) //pb is short one
		{
			for (--pa; pa != a; --pa)
			{
				result.push(*pa);
			}
			result.push(*pa);
		}
		else {
			//can not happend
			throw;
		}

		return result;
	}
};