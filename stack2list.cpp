#include <iostream>
#include <stack>
#include <thread>
#include <mutex>

using namespace std;



class stackempty :public exception {

public:
	stackempty() :exception("pop empty stack.\n")
	{
	}
};

template<class TTTT>
class mylist {
private:
	std::stack<TTTT> stackpush;
	std::mutex stackpushlock;

	std::stack<TTTT> stackpop;
	std::mutex stackpoplock;

	std::mutex dumplock;
public:
	mylist & push(TTTT&& num) {
		std::lock_guard<std::mutex> lock(stackpushlock);
		stackpush.push(std::forward<TTTT>(num));
		return *this;
	}

	TTTT& prepop() {
		std::lock_guard<std::mutex> lock(stackpoplock);

		if (stackpop.empty())
			throw stackempty();
		TTTT& v = stackpop.top();
		stackpop.pop();
		return v;
	}

	//如果没有数据,则会在此阻塞
	TTTT& finalpop() {
		TTTT v;
		do {
			stackpoplock.lock();
			if (!stackpop.empty())
			{
				v = stackpop.top();
				stackpop.pop();
				stackpoplock.unlock();
				break;
			}
			stackpoplock.unlock();
			std::this_thread::sleep_for(std::chrono::microseconds(100));
			dumpdata();
		} while (true);

		return v;
	}

	TTTT& pop() {
		TTTT v;
		try {
			v = prepop();
		}
		catch (stackempty& s) {
			cout << s.what() << endl;
			if (dumpdata())
				v = finalpop();
		}
		
		return v;
	}

	bool dumpdata() {
		std::unique_lock<std::mutex> dlock(dumplock, std::defer_lock);
		std::unique_lock<std::mutex> pushlock(dumplock, std::defer_lock);
		std::unique_lock<std::mutex> poplock(dumplock, std::defer_lock);

		//std::lock(dlock, pushlock, poplock);

		if (stackpop.empty())
			while (!stackpush.empty()) {
				stackpop.push(stackpush.top());
				stackpush.pop();
			}

		if (stackpop.empty())
			return false;
		else
			return true;
	}
	
};

int main() {
	mylist<int> sa;
	sa.push(1).push(2).push(3).push(4);
	cout << sa.pop() << sa.pop() << endl; //先执行第2个pop的

	sa.push(5).push(6).push(7).push(8);
	cout << sa.pop() << sa.pop() << endl;
	cout << sa.pop() << sa.pop() << endl;
	cout << sa.pop() << sa.pop() << endl;

	cin.get();
	return 0;
}