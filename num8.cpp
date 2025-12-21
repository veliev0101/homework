#include <iostream>
#include <vector>
using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class Rectangle {
private:
    double width;
    double height;
    Point bottomLeft;
    
public:
    explicit Rectangle(double w = 1, double h = 1, double x = 0, double y = 0) 
        : width(w), height(h), bottomLeft(x, y) {
        if (w <= 0 || h <= 0) {
            width = 1;
            height = 1;
        }
    }
    
    Rectangle(const Rectangle& other) 
        : width(other.width), height(other.height), bottomLeft(other.bottomLeft) {}
    
    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            bottomLeft = other.bottomLeft;
        }
        return *this;
    }
    
    vector<Point> getAllCorners() const {
        vector<Point> corners;
        corners.push_back(bottomLeft);
        corners.push_back(Point(bottomLeft.x + width, bottomLeft.y));
        corners.push_back(Point(bottomLeft.x + width, bottomLeft.y + height));
        corners.push_back(Point(bottomLeft.x, bottomLeft.y + height));
        return corners;
    }
    
    bool Intersects(const Rectangle& other) const {
        if (bottomLeft.x > other.bottomLeft.x + other.width) return false;
        if (bottomLeft.x + width < other.bottomLeft.x) return false;
        if (bottomLeft.y > other.bottomLeft.y + other.height) return false;
        if (bottomLeft.y + height < other.bottomLeft.y) return false;
        return true;
    }
    
    bool contains(const Point& p) const {
        return p.x >= bottomLeft.x && p.x <= bottomLeft.x + width &&
               p.y >= bottomLeft.y && p.y <= bottomLeft.y + height;
    }
    
    Rectangle& moveTo(double x, double y) {
        bottomLeft.x = x;
        bottomLeft.y = y;
        return *this;
    }
    
    Rectangle& resize(double w, double h) {
        if (w > 0) width = w;
        if (h > 0) height = h;
        return *this;
    }
    
    void printInfo() const {
        cout << "Rect: (" << bottomLeft.x << ", " << bottomLeft.y << ") ";
        cout << "size: " << width << "x" << height << endl;
    }
};

void testRectangles() {
    cout << "=== Testing Rectangles ===\n" << endl;
    
    cout << "1. Creating rectangles" << endl;
    Rectangle r1(5, 3, 1, 1);
    Rectangle r2(4, 2, 3, 2);
    Rectangle r3(2, 2, 10, 10);
    
    r1.printInfo();
    r2.printInfo();
    r3.printInfo();
    
    cout << "\n2. Testing Intersects()" << endl;
    cout << "r1 and r2 intersect: " << (r1.Intersects(r2) ? "yes" : "no") << endl;
    cout << "r1 and r3 intersect: " << (r1.Intersects(r3) ? "yes" : "no") << endl;
    
    cout << "\n3. Testing contains()" << endl;
    Point p1(2, 2);
    Point p2(20, 20);
    cout << "r1 contains (2,2): " << (r1.contains(p1) ? "yes" : "no") << endl;
    cout << "r1 contains (20,20): " << (r1.contains(p2) ? "yes" : "no") << endl;
    
    cout << "\n4. Testing chaining methods" << endl;
    Rectangle r4(3, 3);
    r4.printInfo();
    r4.moveTo(5, 5).resize(7, 2);
    r4.printInfo();
    
    cout << "\n5. Testing copy constructor" << endl;
    Rectangle r5 = r1;
    cout << "Original: ";
    r1.printInfo();
    cout << "Copy: ";
    r5.printInfo();
    
    cout << "\n6. Testing assignment operator" << endl;
    Rectangle r6(1, 1);
    r6 = r2;
    cout << "Assigned: ";
    r6.printInfo();
    
    cout << "\n7. Testing getAllCorners()" << endl;
    vector<Point> corners = r1.getAllCorners();
    cout << "Corners of r1:" << endl;
    for (int i = 0; i < corners.size(); i++) {
        cout << "  (" << corners[i].x << ", " << corners[i].y << ")" << endl;
    }
    
    cout << "\n8. Testing const objects" << endl;
    const Rectangle constRect(2, 3, 0, 0);
    cout << "Const rect corners: " << constRect.getAllCorners().size() << endl;
    cout << "Contains (1,1): " << constRect.contains(Point(1, 1)) << endl;
    
    cout << "\n9. Edge cases - no intersection" << endl;
    Rectangle r7(2, 2, 0, 0);
    Rectangle r8(2, 2, 5, 5);
    cout << "Far apart rectangles intersect: " << (r7.Intersects(r8) ? "yes" : "no") << endl;
    
    cout << "\n10. Touching rectangles" << endl;
    Rectangle r9(2, 2, 0, 0);
    Rectangle r10(2, 2, 2, 0);
    cout << "Touching at edge: " << (r9.Intersects(r10) ? "yes" : "no") << endl;
}

int main() {
    testRectangles();
    cout << "\nAll tests completed" << endl;
    return 0;
}