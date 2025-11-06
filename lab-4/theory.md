## Inheritance

Inheritance is a fundamental concept in object-oriented programming (OOP) that allows a new class, known as a subclass or derived class, to inherit properties and behaviors (attributes and methods) from an existing class, known as a superclass or base class. This mechanism promotes code reusability and establishes a hierarchical relationship between classes.

### Types of Inheritance

1. **Single Inheritance**: A subclass inherits from one superclass.

   ```cpp
   class Base {
   public:
       void display() {
           std::cout << "Base class display function" << std::endl;
       }
   };

   class Derived : public Base {
   };
   ```

2. **Multiple Inheritance**: A subclass inherits from more than one superclass.

   ```cpp
    class Base1 {
    public:
         void display1() {
              std::cout << "Base1 class display function" << std::endl;
         }
    };
    class Base2 {
    public:
            void display2() {
                std::cout << "Base2 class display function" << std::endl;
            }
        };
    class Derived : public Base1, public Base2 {
    };
   ```

3. **Multilevel Inheritance**: A subclass inherits from a superclass, which in turn inherits from another superclass.

   ```cpp
   class Grandparent {
   public:
        void show() {
             std::cout << "Grandparent class show function" << std::endl;
        }
   };

   class Parent : public Grandparent {
   };

   class Child : public Parent {
   };
   ```

### Key Points about Inheritance

- Inheritance allows for code reusability by enabling subclasses to use methods and attributes of their superclasses.
- Access specifiers (`public`, `protected`, `private`) determine the visibility of inherited members in the subclass.
- Constructors and destructors of the base class are not inherited but can be called from the derived class.
- In the case of multiple inheritance, if two base classes have a member with the same name, the derived class must specify which base class's member to use.

### Example of Inheritance

```cpp

#include <iostream>
class Animal {
public:
    void eat() {
        std::cout << "This animal eats food." << std::endl;
    }
};

class Dog : public Animal {
public:
    void bark() {
        std::cout << "The dog barks." << std::endl;
    }
};

int main() {
    Dog myDog;
    myDog.eat(); // Inherited from Animal class
    myDog.bark(); // Defined in Dog class
    return 0;
}

```
