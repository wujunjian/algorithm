#include <iostream>
#include <stack>

//test with -fno-elide-constructors

using namespace std;
class A
{
public:
    A():m_ptr(new int(0)){cout << "construct" << endl;}
    A(const A& a):m_ptr(new int(*a.m_ptr)) //深拷贝的拷贝构造函数
    {
        cout << "copy construct" << endl;
    }
    ~A(){ delete m_ptr;}
private:
    int* m_ptr;
};


A GetA()
{
	return A();
}

int main() {
    A a = GetA();

	std::stack<int> sa;
	cout << sa.top() << endl;
	cin.get();
    return 0;
}
