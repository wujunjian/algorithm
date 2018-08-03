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

	std::stack<char> xor(const char* a, const char* b)
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
	

	int count1(int n)
	{
		
		int res = 0;
		if (n < 0)
		{//
			res = 1;
			n = -n;
		}
			
		while (n != 0)
		{
			res += n & 1;
			n >>= 1; // n>>>=1 c++ Ã»ÓĞÎŞ·ûºÅÓÒÒÆ 
		}
		return res;
	}

	int count2(int n)
	{
		int res = 0;
		if (n < 0)
		{
			res = 1;
			n = -n;
		}
		while (n != 0)
		{
			n &= (n - 1);
			++res;
		}
		return res;
	}

	int ParallelCount(int n)
	{
		n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
		n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
		n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
		n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
		n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
		return n;
	}
};