#include <iostream>
#include <map>

using namespace std;
int main() {
	std::map<int, char> example = { {1, 'a'}, {2, 'b'} };

	auto search = example.find(2);
	if (search != example.end()) {
		cout << "Found " << search->first << " " << search->second << endl;
	}
	else {
		cout << "Not found" << endl;
	}
	cin.get();
	return 0;
}