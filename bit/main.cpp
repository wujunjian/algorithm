#include <iostream>
#include "util.h"

using namespace std;

int main()
{
	cout << util::getmax(1, -2) << endl;
	
	cout << util::add(999999999999999999, (long long)33) << endl;
	

	auto sc = util:: xor ("123", "3212");
	cin.get();
	return 0;
}