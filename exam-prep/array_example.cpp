#include <iostream>
#include <list>

int main()
{
    // Define an empty list of integers
    std::list<int> myList;

    // Define a list with initial values
    std::list<int> numbers = {1, 2, 3, 4, 5};

    // Add elements to the list
    myList.push_back(10); // Add to end
    myList.push_front(5); // Add to beginning

    // Iterate through the list
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Access size
    std::cout << "Size: " << numbers.size() << std::endl;

    // Remove elements
    numbers.pop_front(); // Remove first element
    numbers.pop_back();  // Remove last element

    return 0;
}
// Dynamic list example - list grows/shrinks at runtime
void dynamicListExample()
{
    std::list<int> dynamicList;

    std::cout << "\n--- Dynamic List Example ---" << std::endl;

    // Dynamically add elements
    for (int i = 1; i <= 5; i++)
    {
        dynamicList.push_back(i * 10);
        std::cout << "Added " << i * 10 << ", Size: " << dynamicList.size() << std::endl;
    }

    // Display current list
    std::cout << "Current list: ";
    for (int val : dynamicList)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Dynamically remove elements
    while (!dynamicList.empty())
    {
        std::cout << "Removing " << dynamicList.front() << ", Size: " << dynamicList.size() << std::endl;
        dynamicList.pop_front();
    }

    std::cout << "List is now empty: " << (dynamicList.empty() ? "Yes" : "No") << std::endl;
}

// Array example - fixed size, defined at compile time
void arrayExample()
{
    std::cout << "\n--- Array Example ---" << std::endl;

    // Define array with fixed size
    int arr[5] = {10, 20, 30, 40, 50};

    // Access elements by index
    std::cout << "First element: " << arr[0] << std::endl;
    std::cout << "Last element: " << arr[4] << std::endl;

    // Iterate through array
    std::cout << "All elements: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Modify elements
    arr[2] = 100;
    std::cout << "Modified element at index 2: " << arr[2] << std::endl;
}
