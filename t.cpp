#include <iostream>
#include <stack>
#include <set>

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

int setmain() {
	set<int> seta;
	seta.insert(1);
	seta.insert(2);
	seta.insert(1);
	cout << seta.size() << endl;
	return 0;
}
int main () {

    A a = GetA();

	std::stack<int> sa;
	cout << sa.top() << endl;
	cin.get();
    return 0;
}
