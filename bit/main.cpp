#include <iostream>
#include "util.h"

using namespace std;

int main()
{
	list<int> ls;
	ls.push_back(1);
	ls.push_back(1);
	ls.push_back(3);
	ls.push_back(3);
	ls.push_back(9);
	ls.push_back(8);

	cout << util::get1TimesOddNum(ls) << endl;

	util::get2TimesOddNum(ls);
	for (int n : ls)
		cout << n << endl;
	cin.get();

	return 0;
}

int main22()
{
	cout << util::count2(-5) << endl;


	cout << util::ParallelCount(-8552) << endl;

	cin.get();
	return 0;
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