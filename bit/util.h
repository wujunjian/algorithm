#pragma once



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


	//TODO change int to  std::array<char,32>
	inline int add(int a, int b)
	{
		int sum = a;
		while (b != 0)
		{
			sum = a ^ b;
			b = (a&b) << 1;
			a = sum;
		}
		return sum;
	}


};