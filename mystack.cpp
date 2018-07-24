#include <vector>
#include <iostream>
#include <stdexcept>


using namespace std;

class Mystack {
private:
    vector<int> stackData;
    vector<int> stackMin;

public:
    Mystack() {
        
    }

    Mystack& push(int newNum) {
        if(stackMin.empty() || stackMin.back() >= newNum)
        {
            stackMin.push_back(newNum);
        } 
        stackData.push_back(newNum);
        return *this;
    }
    int pop() {
        if(stackData.empty()) {
            throw std::runtime_error("the stack is empty");
        } 

        if(stackData.back() == stackMin.back())
        {
            stackMin.pop_back();
        }
        int value = stackData.back();
        stackData.pop_back();
        return value;
    }
    int getmin() {
         return stackMin.back();
    }
};


int main(){

    class Mystack s;
    s.push(3).push(4).push(5).push(1).push(2).push(1);
    cout << "s.push(3).push(4).push(5).push(1).push(2).push(1);" << endl;
    cout <<  "min:" << s.getmin() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.getmin() << endl;
    return 0;
}


