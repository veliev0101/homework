#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T, int Capacity>
class Stack {
private:
    T data[Capacity];
    int topIndex;
    
public:
    Stack() : topIndex(-1) {}
    
    void push(const T& value) {
        if (full()) {
            throw overflow_error("Stack is full");
        }
        data[++topIndex] = value;
    }
    
    T pop() {
        if (empty()) {
            throw underflow_error("Stack is empty");
        }
        return data[topIndex--];
    }
    
    const T& top() const {
        if (empty()) {
            throw underflow_error("Stack is empty");
        }
        return data[topIndex];
    }
    
    bool empty() const {
        return topIndex == -1;
    }
    
    bool full() const {
        return topIndex == Capacity - 1;
    }
    
    int size() const {
        return topIndex + 1;
    }
};

int main() {
    cout << "=== Testing int Stack ===" << endl;
    Stack<int, 5> s1;
    
    cout << "Stack empty? " << (s1.empty() ? "yes" : "no") << endl;
    
    s1.push(10);
    s1.push(20);
    s1.push(30);
    
    cout << "Size: " << s1.size() << endl;
    cout << "Top: " << s1.top() << endl;
    
    cout << "Pop: " << s1.pop() << endl;
    cout << "Now top: " << s1.top() << endl;
    cout << "Size: " << s1.size() << endl;
    
    s1.push(40);
    s1.push(50);
    s1.push(60);
    
    cout << "Stack full? " << (s1.full() ? "yes" : "no") << endl;
    
    cout << "\n=== Testing string Stack ===" << endl;
    Stack<string, 3> s2;
    
    s2.push("hello");
    s2.push("world");
    s2.push("test");
    
    cout << "Size: " << s2.size() << endl;
    cout << "Top: " << s2.top() << endl;
    
    while (!s2.empty()) {
        cout << "Pop: " << s2.pop() << endl;
    }
    
    cout << "\n=== Testing errors ===" << endl;
    Stack<double, 2> s3;
    
    try {
        s3.pop();
    } catch (const underflow_error& e) {
        cout << "Error on pop: " << e.what() << endl;
    }
    
    s3.push(1.5);
    s3.push(2.5);
    
    try {
        s3.push(3.5);
    } catch (const overflow_error& e) {
        cout << "Error on push: " << e.what() << endl;
    }
    
    cout << "\n=== Testing full operations ===" << endl;
    Stack<char, 4> s4;
    
    s4.push('a');
    s4.push('b');
    s4.push('c');
    s4.push('d');
    
    cout << "Size: " << s4.size() << endl;
    cout << "Full? " << (s4.full() ? "yes" : "no") << endl;
    
    while (!s4.empty()) {
        cout << s4.pop() << " ";
    }
    cout << endl;
    
    cout << "Empty? " << (s4.empty() ? "yes" : "no") << endl;
    
    return 0;
}