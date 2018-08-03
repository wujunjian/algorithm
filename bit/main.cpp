#include <iostream>
#include "util.h"

using namespace std;

int main()
{
	cout << util::count2(-5) << endl;


	cout << util::ParallelCount(-8552) << endl;

	cin.get();
}


int main11()
{
	cout << util::getmax(1, -2) << endl;
	
	cout << util::add(999999999999999999, (long long)33) << endl;
	
	//1==>0x31  2==>0x32 3==>0x33
	std::stack<char>&& sc = util:: xor ("123", "3212");
	while (sc.size())
	{
		cout << int(sc.top()) << endl;
		sc.pop();
	}
	
	cin.get();
	return 0;
}