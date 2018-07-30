#include <stack>
#include <cassert>
#include <iostream>


using namespace std;

int getandremovelastelement(stack<int>& mystack)
{
	assert(!mystack.empty());
	int result = mystack.top();
	mystack.pop();
	if (!mystack.empty())
	{
		int last = getandremovelastelement(mystack);
		mystack.push(result);
		return last;
	}		
	else
		return result;
}

void reverse(stack<int>& mystack)
{
	if (mystack.empty())
		return;

	int i = getandremovelastelement(mystack);
	reverse(mystack);
	mystack.push(i);
}

int main() {

	std::deque<int> deq { 10, 9, 8,7,6,5,4,3,2,1,0};
	stack<int> mystack(deq);


	cout << mystack.top() << endl;

	reverse(mystack);

	for (;!mystack.empty(); mystack.pop())
	{
		cout << mystack.top() << endl;
	}


	cin.get();
	return 0;
}