#pragma once



namespace util {

	static int flip(int n) {
		return n ^ 1;
	}

	static int sign(int n) {
		return flip((n >> 31) & 1);
	}

	static int getmax(int a, int b) {
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

};