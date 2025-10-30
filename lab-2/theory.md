## 1. Introduction

### Friendship in C++

In C++, the `friend` keyword allows a class or function to access the private and protected members of another class. This is useful when two or more classes need to work closely together, allowing them to share data and functionality without exposing that data to the outside world.

### Example of Friendship

```cpp
#include <iostream>
using namespace std;
class Box {
    private:
     double width;

    public:
     Box(double w) : width(w) {}

     // Declare friend function
     friend void printWidth(Box box);
    };

void printWidth(Box box) {
    cout << "Width of box: " << box.width << endl;
}
int main() {
    Box box(10.0);
    printWidth(box); // Accessing private member through friend function
    return 0;
}
```

### Key Points about Friendship

1. **Non-Member Function**: A friend function is not a member of the class but has access to its private and protected members.

2. **Class Friendship**: A class can declare another class as a friend, allowing all member functions of the friend class to access its private and protected members.

3. **One-Way Relationship**: Friendship is not reciprocal. If class A is a friend of class B, class B does not automatically become a friend of class A.

4. **Granularity**: Friendship can be granted to specific functions or entire classes, providing flexibility in access control.

### When to Use Friendship

- When two or more classes need to work closely together and share data.
- When you want to allow specific functions or classes to access private data without exposing it to the entire world.
