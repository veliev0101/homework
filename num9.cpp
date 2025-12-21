#include <iostream>
#include <cmath>
using namespace std;

class Vector3D {
private:
    double x, y, z;
    mutable double cached_len;
    mutable bool cache_ok;
    static int count;
    
    friend class Vector3DTest;
    
public:
    Vector3D(double a = 0.0, double b = 0.0, double c = 0.0) 
        : x(a), y(b), z(c), cache_ok(false) {
        count++;
    }
    
    Vector3D(const Vector3D& other) 
        : x(other.x), y(other.y), z(other.z), cache_ok(false) {
        count++;
    }
    
    ~Vector3D() {
        count--;
    }
    
    double getLength() const {
        if (!cache_ok) {
            cached_len = sqrt(x*x + y*y + z*z);
            cache_ok = true;
        }
        return cached_len;
    }
    
    Vector3D normalize() const {
        double len = getLength();
        if (len < 0.000001) {
            return Vector3D(0, 0, 0);
        }
        return Vector3D(x/len, y/len, z/len);
    }
    
    static double dot(const Vector3D& a, const Vector3D& b) {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }
    
    bool operator()(double val) const {
        return fabs(x - val) < 0.00001 || 
               fabs(y - val) < 0.00001 || 
               fabs(z - val) < 0.00001;
    }
    
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    
    Vector3D operator*(double num) const {
        return Vector3D(x * num, y * num, z * num);
    }
    
    bool operator==(const Vector3D& other) const {
        return fabs(x - other.x) < 0.00001 &&
               fabs(y - other.y) < 0.00001 &&
               fabs(z - other.z) < 0.00001;
    }
    
    bool operator!=(const Vector3D& other) const {
        return !(*this == other);
    }
    
    friend ostream& operator<<(ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
    
    static int getCount() {
        return count;
    }
};

int Vector3D::count = 0;

class Vector3DTest {
public:
    static void testCount() {
        cout << "Test count..." << endl;
        int start = Vector3D::getCount();
        Vector3D v1(1, 2, 3);
        Vector3D v2(4, 5, 6);
        cout << "Count after 2 vectors: " << Vector3D::getCount() << endl;
        {
            Vector3D v3(7, 8, 9);
            cout << "Count inside block: " << Vector3D::getCount() << endl;
        }
        cout << "Count after block: " << Vector3D::getCount() << endl;
    }
    
    static void testCache() {
        cout << "\nTest cache..." << endl;
        Vector3D v(3, 4, 0);
        double len1 = v.getLength();
        double len2 = v.getLength();
        cout << "Length first time: " << len1 << endl;
        cout << "Length second time: " << len2 << endl;
    }
    
    static void testMath() {
        cout << "\nTest math operations..." << endl;
        Vector3D a(1, 2, 3);
        Vector3D b(4, 5, 6);
        
        Vector3D sum = a + b;
        cout << a << " + " << b << " = " << sum << endl;
        
        Vector3D diff = a - b;
        cout << a << " - " << b << " = " << diff << endl;
        
        Vector3D mul = a * 3;
        cout << a << " * 3 = " << mul << endl;
    }
    
    static void testCompare() {
        cout << "\nTest compare..." << endl;
        Vector3D v1(1.0, 2.0, 3.0);
        Vector3D v2(1.0, 2.0, 3.0);
        Vector3D v3(1.1, 2.1, 3.1);
        
        cout << v1 << " == " << v2 << " ? " << (v1 == v2 ? "yes" : "no") << endl;
        cout << v1 << " == " << v3 << " ? " << (v1 == v3 ? "yes" : "no") << endl;
    }
    
    static void testDot() {
        cout << "\nTest dot product..." << endl;
        Vector3D v1(1, 0, 0);
        Vector3D v2(0, 1, 0);
        cout << v1 << " dot " << v2 << " = " << Vector3D::dot(v1, v2) << endl;
        
        Vector3D v3(1, 2, 3);
        Vector3D v4(4, 5, 6);
        cout << v3 << " dot " << v4 << " = " << Vector3D::dot(v3, v4) << endl;
    }
    
    static void testNormal() {
        cout << "\nTest normalize..." << endl;
        Vector3D v(3, 4, 0);
        Vector3D n = v.normalize();
        cout << "Vector: " << v << endl;
        cout << "Normalized: " << n << endl;
        cout << "Length of normalized: " << n.getLength() << endl;
    }
    
    static void testFunctor() {
        cout << "\nTest operator() ..." << endl;
        Vector3D v(2.5, 3.5, 4.5);
        cout << "Vector " << v << " has 2.5? " << (v(2.5) ? "yes" : "no") << endl;
        cout << "Vector " << v << " has 10? " << (v(10) ? "yes" : "no") << endl;
    }
    
    static void runAll() {
        cout << "=== Start tests ===" << endl;
        testCount();
        testCache();
        testMath();
        testCompare();
        testDot();
        testNormal();
        testFunctor();
        cout << "=== Tests done ===" << endl;
    }
};

int main() {
    cout << "Simple Vector3D demo\n" << endl;
    
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    
    cout << "v1 length = " << v1.getLength() << endl;
    
    Vector3D v3 = v1 + v2;
    cout << "v1 + v2 = " << v3 << endl;
    
    Vector3D v4 = v1 * 2.5;
    cout << "v1 * 2.5 = " << v4 << endl;
    
    Vector3D v5 = v1.normalize();
    cout << "Normalized v1 = " << v5 << endl;
    
    double d = Vector3D::dot(v1, v2);
    cout << "v1 dot v2 = " << d << endl;
    
    cout << "\nUsing (): v1 has 2? " << (v1(2) ? "yes" : "no") << endl;
    cout << "v1 has 10? " << (v1(10) ? "yes" : "no") << endl;
    
    cout << "\nVector count now: " << Vector3D::getCount() << endl;
    
    cout << "\n";
    Vector3DTest::runAll();
    
    return 0;
}