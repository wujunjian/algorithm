#include <iostream>
#include <map>

using namespace std;
int main() {
	std::map<int, char> example = { {8, 'a'}, {1, 'b'},{ 5, 'b' },{ 4, 'b' } };

	auto search = example.find(2);
	if (search != example.end()) {
		cout << "Found " << search->first << " " << search->second << endl;
	}
	else {
		cout << "Not found" << endl;
	}

	std::map<int, char>::iterator iter = example.begin();
	for (; iter != example.end(); ++iter)
	{
		cout << iter->first << ":" << iter->second << endl;
	}
	cin.get();
	return 0;
}