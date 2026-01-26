#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
    // Define an empty list of integers
    list<int> myList;

    // Define a list with initial values
    list<int> numbers = {1, 2, 3, 4, 5};

    // Add elements to the list
    myList.push_back(10); // Add to end
    myList.push_front(5); // Add to beginning

    // Iterate through the list
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;

    // Access size
    cout << "Size: " << numbers.size() << endl;

    // Remove elements
    numbers.pop_front(); // Remove first element
    numbers.pop_back();  // Remove last element

    return 0;
}
// Dynamic list example - list grows/shrinks at runtime
void dynamicListExample()
{
    list<int> dynamicList;

    cout << "\n--- Dynamic List Example ---" << endl;

    // Dynamically add elements
    for (int i = 1; i <= 5; i++)
    {
        dynamicList.push_back(i * 10);
        cout << "Added " << i * 10 << ", Size: " << dynamicList.size() << endl;
    }

    // Display current list
    cout << "Current list: ";
    for (int val : dynamicList)
    {
        cout << val << " ";
    }
    cout << endl;

    // Dynamically remove elements
    while (!dynamicList.empty())
    {
        cout << "Removing " << dynamicList.front() << ", Size: " << dynamicList.size() << endl;
        dynamicList.pop_front();
    }

    cout << "List is now empty: " << (dynamicList.empty() ? "Yes" : "No") << endl;
}

// Array example - fixed size, defined at compile time
void arrayExample()
{
    cout << "\n--- Array Example ---" << endl;

    // Define array with fixed size
    int arr[5] = {10, 20, 30, 40, 50};

    // Access elements by index
    cout << "First element: " << arr[0] << endl;
    cout << "Last element: " << arr[4] << endl;

    // Iterate through array
    cout << "All elements: ";
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Modify elements
    arr[2] = 100;
    cout << "Modified element at index 2: " << arr[2] << endl;
}
// Dynamic array example - using new/delete
void dynamicArrayExample()
{
    cout << "\n--- Dynamic Array Example ---" << endl;

    int size;
    cout << "Enter array size: ";
    cin >> size;

    // Allocate dynamic array
    int *dynamicArr = new int[size];

    // Initialize elements
    for (int i = 0; i < size; i++)
    {
        dynamicArr[i] = (i + 1) * 10;
    }

    // Display elements
    cout << "Dynamic array elements: ";
    for (int i = 0; i < size; i++)
    {
        cout << dynamicArr[i] << " ";
    }
    cout << endl;

    // Clean up - free memory
    delete[] dynamicArr;
    cout << "Memory deallocated." << endl;
}
// Class with vector as property
class Student
{
private:
    string name;
    vector<int> grades;

public:
    Student(string n) : name(n) {}

    void addGrade(int grade)
    {
        grades.push_back(grade);
    }

    void displayGrades()
    {
        cout << name << "'s grades: ";
        for (int grade : grades)
        {
            cout << grade << " ";
        }
        cout << endl;
    }

    double getAverage()
    {
        if (grades.empty())
            return 0.0;

        double sum = 0;
        for (int grade : grades)
        {
            sum += grade;
        }
        return sum / grades.size();
    }
};

void vectorPropertyExample()
{
    cout << "\n--- Vector Property Example ---" << endl;

    Student student("Alex");
    student.addGrade(85);
    student.addGrade(90);
    student.addGrade(78);

    student.displayGrades();
    cout << "Average: " << student.getAverage() << endl;
}