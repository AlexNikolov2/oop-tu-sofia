## Aliases

In C++, an alias is a different name for an existing type. Aliases can be created using the `typedef` keyword or the `using` directive. They are often used to improve code readability or to simplify complex type definitions.

### Creating Aliases with `typedef`

```cpp
typedef unsigned int uint;
typedef int (*FuncPtr)(int, int);
```

### Creating Aliases with `using`

```cpp
using uint = unsigned int;
using FuncPtr = int (*)(int, int);
```

### Key Points about Aliases

- Aliases do not create new types; they simply provide a new name for an existing type.
- Aliases can make code more readable by giving meaningful names to complex types.
- Both `typedef` and `using` can be used interchangeably for most use cases, but `using` is generally preferred in modern C++ for its clarity and simplicity.

### When to Use Aliases

- When you want to improve code readability by providing meaningful names to types.
- When dealing with complex type definitions, such as function pointers or template types, to simplify their usage in code.
- When you want to create platform-independent type names (e.g., `uint32_t` for a 32-bit unsigned integer).

### Example of Using Aliases

```cpp
#include <iostream>

using uint = unsigned int;
using FuncPtr = int (*)(int, int);
int add(int a, int b) {
    return a + b;
}
int main() {
    uint x = 10;
    uint y = 20;
    FuncPtr func = add;
    std::cout << "Sum: " << func(x, y) << std::endl; // Output: Sum: 30
    return 0;
}
```
