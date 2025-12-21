#include <iostream>
#include <stdexcept>
using namespace std;

class SafeArray {
private:
    int* arr;
    int sz;
    
public:
    SafeArray(int n) : sz(n) {
        if (n <= 0) {
            throw invalid_argument("Bad size");
        }
        arr = new int[n]();
    }
    
    ~SafeArray() noexcept {
        delete[] arr;
    }
    
    SafeArray(const SafeArray& other) : sz(other.sz) {
        arr = new int[sz];
        for (int i = 0; i < sz; i++) {
            arr[i] = other.arr[i];
        }
    }
    
    SafeArray& operator=(const SafeArray& other) {
        if (this == &other) return *this;
        
        int* newArr = new int[other.sz];
        for (int i = 0; i < other.sz; i++) {
            newArr[i] = other.arr[i];
        }
        
        delete[] arr;
        arr = newArr;
        sz = other.sz;
        return *this;
    }
    
    int& operator[](int idx) {
        if (idx < 0 || idx >= sz) {
            throw out_of_range("Bad index");
        }
        return arr[idx];
    }
    
    const int& operator[](int idx) const {
        if (idx < 0 || idx >= sz) {
            throw out_of_range("Bad index");
        }
        return arr[idx];
    }
    
    void resize(int newSize) {
        if (newSize > 1000) {
            throw length_error("Too big");
        }
        
        if (newSize == sz) return;
        
        int* newArr = new int[newSize]();
        
        int smaller = newSize < sz ? newSize : sz;
        for (int i = 0; i < smaller; i++) {
            newArr[i] = arr[i];
        }
        
        delete[] arr;
        arr = newArr;
        sz = newSize;
    }
    
    int size() const {
        return sz;
    }
    
    void fill(int val) {
        for (int i = 0; i < sz; i++) {
            arr[i] = val;
        }
    }
};

int main() {
    cout << "Testing SafeArray\n" << endl;
    
    try {
        cout << "Test 1: Bad size" << endl;
        SafeArray a1(-5);
    } catch (const invalid_argument& e) {
        cout << "Got error: " << e.what() << "\n" << endl;
    }
    
    try {
        cout << "Test 2: Good array" << endl;
        SafeArray a2(3);
        a2[0] = 10;
        a2[1] = 20;
        a2[2] = 30;
        cout << "a2[1] = " << a2[1] << "\n" << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    try {
        cout << "Test 3: Bad index" << endl;
        SafeArray a3(5);
        a3[10] = 100;
    } catch (const out_of_range& e) {
        cout << "Got error: " << e.what() << "\n" << endl;
    }
    
    try {
        cout << "Test 4: Copy" << endl;
        SafeArray a4(4);
        a4.fill(7);
        SafeArray a5 = a4;
        cout << "a5[2] = " << a5[2] << "\n" << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    try {
        cout << "Test 5: Resize too big" << endl;
        SafeArray a6(10);
        a6.resize(2000);
    } catch (const length_error& e) {
        cout << "Got error: " << e.what() << "\n" << endl;
    }
    
    try {
        cout << "Test 6: Good resize" << endl;
        SafeArray a7(3);
        a7[0] = 1;
        a7[1] = 2;
        a7[2] = 3;
        a7.resize(5);
        a7[4] = 99;
        cout << "a7[4] = " << a7[4] << "\n" << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    try {
        cout << "Test 7: Assignment" << endl;
        SafeArray a8(2);
        a8[0] = 8;
        a8[1] = 9;
        
        SafeArray a9(1);
        a9 = a8;
        cout << "a9[1] = " << a9[1] << "\n" << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "All tests done" << endl;
    return 0;
}