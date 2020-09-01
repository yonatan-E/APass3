# C++ Coding Standards Part 0: Automated Code Analysis

Automated analysis is the main advantage to working with a modern statically typed compiled language like C++. Code analysis tools can inform us when we have implemented an operator overload with a non-canonical form, when we should have made a method const, or when the scope of a variable can be reduced.

In short, these tools catch the most commonly agreed best practice mistakes we are making and help educate us to write better code. We will be fully utilizing these tools.

## Compilers

All reasonable warning levels should be enabled. Some warning levels, such as GCC's `-Weffc++` warning mode can be too noisy and will not be recommended for normal compilation.

### GCC / Clang

A good combination of settings is `-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic`

 * `-Wall -Wextra`: reasonable and standard
 * `-Wshadow`: warn the user if a variable declaration shadows another with the same name in the same scope
 * `-Wnon-virtual-dtor`: warn the user if a class with virtual functions has a non-virtual destructor. This can lead to hard to track down memory errors
 * `-pedantic`: warn about non-portable code, C++ that uses language extensions.


## Static Analyzers

Static analyzers look for errors that compilers do not look for, such as potential performance and memory issues.

## Ignoring Warnings

If you determine that the compiler or analyzer is warning on something that is either incorrect or unavoidable, disable the specific error to as localized part of the code as possible.

## Unit Tests

There should be a test enabled for every feature or bug fix that is committed. See also "Code Coverage Analysis."


# C++ Coding Standards Part 1: Style

Style guidelines are not overly strict. The important thing is that code is clear and readable with an appropriate amount of whitespace and reasonable length lines. A few best practices are also mentioned, and many are not.

## Descriptive and Consistent Naming

C++ allows for arbitrary length identifier names, so there's no reason to be terse when naming variables. Use descriptive names, and be consistent in the style

 * `CamelCase`
 * `camelCase`
 * `snake_case`
 
are common examples.

### Common C++ Naming Conventions

 * Types start with capitals: `MyClass`
 * functions and variables start with lower case: `myMethod`
 * constants are all capital: `const int PI=3.14159265358979323;`

### Distinguish Private Object Data

Name private data with a `m_` prefix to distinguish it from public data.

### Distinguish Global and Static Data

In general, global and static data should be avoided. If used, 
name static data with a `s_` prefix and name global data with a `g_` prefix.

`constexpr static` data should be treated as a constant, and be name as such.

### Don't Name Anything Starting With _
If you do, you risk colliding with names reserved for compiler and standard library implementation use.


### Well formed example

```cpp
static constexpr unsigned int ARRAY_SIZE = 10;
int g_value;

class MyClass
{
  static int s_count;
public:
  MyClass(int data)
    : m_data(data)
  {
  }
  
  int getData() const
  {
    return m_data;
  }
  
private:
  int m_data;
};

int MyClass::s_count;
```

## Consistency

Many choices are up to the developer, e.g. whether to use `snake_case` or `camelCase` for variable names and whether to put the first curly brace of an if-statement in a separate line, but it is very important to be consistent with the choices you make.

## Distinguish C++ Files From C Files

C++ source file should be named `.cpp` or `.cc` NOT `.c`
C++ header files should be named `.h`. When prototypes are declared in the header itself, as in the case of templates, use `.hpp`.

## Use `nullptr`

C++11 introduces `nullptr` which is a special type denoting a null pointer value. This should be used instead of 0 or `NULL` to indicate a null pointer.

## Comments

Comment blocks should use `//`, not `/* */`. Using `//` makes it much easier to comment out a block of code while debugging.

```cpp
// this function does something
int myFunc()
{
}
```

To comment out this function block during debugging we might do:

```cpp
/*
// this function does something
int myFunc()
{
}
*/
```

which would be impossible if the function comment header used `/* */`

## Never Use `using` In a Header File

This causes the name space you are `using` to be pulled into the namespace of the header file.


## Include Guards

Header files must contain an distinctly named include guard to avoid problems with including the same header multiple times or conflicting with other headers from other projects

```cpp
#ifndef MYPROJECT_MYCLASS_HPP
#define MYPROEJCT_MYCLASS_HPP

namespace MyProject {
class MyClass {
};
}

#endif
```

In today's compilers, the non-standard extenstion `#pragma once` is widely supported, and should be used instead of the obsolete include guards.

```cpp
#pragma once

namespace MyProject {
class MyClass {
};
}

```

## {} are required for blocks. 
Leaving them off can lead to semantic errors in the code. They should be used even in one-liners.

```cpp
// Bad Idea
// this compiles and does what you want, but can lead to confusing
// errors if close attention is not paid.
for (int i = 0; i < 15; ++i)
  std::cout << i << std::endl;

// Bad Idea
// the cout is not part of the loop in this case even though it appears to be
int sum = 0;
for (int i = 0; i < 15; ++i)
  ++sum;
  std::cout << i << std::endl;
  
  
// Good Idea
// It's clear which statements are part of the loop (or if block, or whatever)
int sum = 0;
for (int i = 0; i < 15; ++i) {
  ++sum;
  std::cout << i << std::endl;
}
```

## Keep lines a reasonable length

```cpp
// Bad Idea
// hard to follow
if (x && y && myFunctionThatReturnsBool() && caseNumber3 && (15 > 12 || 2 < 3)) { 
}

// Good Idea
// Logical grouping, easier to read
if (x && y && myFunctionThatReturnsBool() 
    && caseNumber3 
    && (15 > 12 || 2 < 3)) { 
}
```


## Use "" For Including Local Files
... `<>` is [reserved for system includes](http://blog2.emptycrate.com/content/when-use-include-verses-include).

```cpp
// Bad Idea. Requires extra -I directives to the compiler
// and goes against standards
#include <string>

#include <includes/MyHeader.hpp>

// Worse Idea
// requires potentially even more specific -I directives and 
// makes code more difficult to package and distribute
#include <string>

#include <MyHeader.hpp>


// Good Idea
// requires no extra params and notifies the user that the file
// is a local file
#include <string>

#include "MyHeader.hpp"
```

## Includes order
Headers should be included in the following order:
1. Corresponding .h file (if any)
1. Headers from the same module
1. Standard library (such as `vector`)
1. System libraries (such as `unistd`,`Windows.h`)
1. External modules

Between each two sections there should be a blank line. When such ordering is not possible, for inclusion constraints, this order can be violated, but one should aim to the cleanest possibility.

## Initialize Member Variables

### Initialize Member Variables with the Member Initizlier List

```cpp
// Bad Idea
class MyClass
{
public:
  MyClass(int value)
  {
    m_value = value;
  }

private:
  int m_value;
};


// Good Idea
// C++'s memeber initializer list is unique to the language and leads to
// cleaner code and potential performance gains that other languages cannot 
// match
class MyClass
{
public:
  MyClass(int value)
    : m_value(value)
  {
  }

private:
  int m_value;
};
```

### Initialize Member Variables by Declaration order
Constructor calls are invoked on inner member by declaration order, and not by calling order, and thus can lead to a confusion. Reordering should raise a compiler warning.

### Assign default values with {}
Prefer {} initialization over = unless you have a strong reason not to.

Forgetting to initialize a member is a source of undefined behavior bugs which are often extremely hard to find.

If the member variable is not expected to change after the initialization, then mark it const.


## Auto whenever possible
You should prefer using auto wherever possible. It makes the code cleaner and easier to maintain.
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// Bad
for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
  std::cout << *it << std::endl;
}

// Good
for (auto it = vec.begin(); it != vec.end(); ++it) {
  std::cout << *it << std::endl;
}

```


## Prefer for-each loops
For-each loops are easier to read, and usually result in faster code. 

This:
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// Bad
for (auto it = vec.begin(); it != vec.end(); ++it) {
  std::cout << *it << std::endl;
}
```
instead of:
```cpp
// Good
for (auto num: vec) {
  std::cout << num << std::endl;
}
```

## Forward Declare when Possible

This:
```cpp
// some header file
class MyClass;

void doSomething(const MyClass &);
```

instead of:

```cpp
// some header file
#include "MyClass.hpp"

void doSomething(const MyClass &);
```

This is a proactive approach to simplify compilation time and rebuilding dependencies.

## Always Use Namespaces

There is almost never a reason to declare an identifier in the global namespaces. Instead, functions and classes should exist in an appropriately named namespaces or in a class inside of a namespace. Identifiers which are placed in the global namespace risk conflicting with identifiers from other (mostly C, which doesn't have namespaces) libraries. When some modules are related to each other, it is a good idea to declare nested namespaces.

## Avoid Compiler Macros

Compiler definitions and macros are replaced by the pre-processor before the compiler is ever run. This can make debugging very difficult because the debugger doesn't know where the source came from.

```cpp
// Good Idea
namespace my_project {
  class Constants {
  public:
    static constexpr double PI = 3.14159;
  }
}

// Bad Idea
#define PI 3.14159;

```

# C++ Coding Standards Part 2: Performance and Safety

## Limit Variable Scope

Variables should be declared as late as possible, and ideally, only when it's possible to initialize the object. Reduced variable scope results in less memory being used, more efficient code in general, and helps the compiler optimize the code further.

```c++
// Good idea
for (int i = 0; i < 15; ++i)
{
  MyObject obj(i);
  // do something with obj
}

// Bad Idea
MyObject obj; // meaningless object initialization
for (int i = 0; i < 15; ++i)
{
  obj = MyObject(i); // unnecessary assignment operation
  // do something with obj
}
// obj is still taking up memory for no reason
```

## Use Exceptions Instead of Return Values to Indicate Error

Exceptions cannot be ignored. Return values, such as using `std::optional`, can be ignored and if not checked can cause crashes or memory errors. An exception, on the other hand, can be caught and handled. Potentially all the way up the highest level of the application with a log and automatic restart of the application.

Stroustrup, the original designer of C++, [makes this point](http://www.stroustrup.com/bs_faq2.html#exceptions-why) much better than I ever could.

## Avoid raw memory access

Raw memory access, allocation and deallocation, are difficult to get correct in C++ without [risking memory errors and leaks](http://blog2.emptycrate.com/content/nobody-understands-c-part-6-are-you-still-using-pointers). C++11 provides tools to avoid these problems.

```cpp
// Bad Idea
MyClass *myobj = new MyClass;

// ...
delete myobj;


// Good Idea
std::shared_ptr<MyClass> myobj = std::make_shared<MyClass>();
// ... 
// myobj is automatically freed for you whenever it is no longer used.
```

## The rule of 5
Whenever a class declared one of the following methods, it should probably declare all of them:
1. `~MyClass()` - Destructor
1. `MyClass(const MyClass&)` - Copy Constructor 
1. `MyClass& operator=(const MyClass&)` - Copy-Assignment operator
1. `MyClass(MyClass&&)` - Move Constructor 
1. `MyClass& operator=(MyClass&)` - Move-Assignment operator

## Consider the Rule of Zero
The Rule of Zero states that you do not provide any of the functions that the compiler can provide (copy constructor, copy assignment operator, move constructor, move assignment operator, destructor) unless the class you are constructing does some novel form of ownership.

The goal is to let the compiler provide optimal versions that are automatically maintained when more member variables are added.

The original article provides the background, while a follow up article explains techniques for implementing nearly 100% of the time.

## Adhere to RAII
Resources should used only according to the `RAII` pattern in order to avoid leaking in exception-throwing environment. 

## Avoid global and static data
This includes singleton objects.

Global data leads to unintended side effects between functions and can make code difficult or impossible to parallelize, debug and read. Even if the code is not intended today for parallelization, there is no reason to make it impossible for the future.


## Prefer pre-increment to post-increment 
... when it is semantically correct. Pre-increment is [faster](http://blog2.emptycrate.com/content/why-i-faster-i-c) then post-increment because it does not require a copy of the object to be made.

```cpp
// Bad Idea
for (int i = 0; i < 15; i++) {
  std::cout << i << std::endl;
}


// Good Idea
for (int i = 0; i < 15; ++i) {
  std::cout << i << std::endl;
}

```


## Const as much as possible
`const` tells the compiler that a variable or method is immutable. This helps the compiler optimize the code and helps the developer know if a function side effects. Also, using `const &` prevents the compiler from copying data unnecessarily. STL iterator also support constness, offering the methods `cbegin`, `cend` and the standard sub-type `const_iterator`. 

```cpp
// Bad Idea
class MyClass
{
public:
  MyClass(std::string value)
    : m_value(value)
  {
  }

  std::string get_value() 
  {
    return m_value;
  }

private:
  std::string m_value;
}


// Good Idea
class MyClass
{
public:
  MyClass(const std::string &value)
    : m_value(value)
  {
  }

  std::string get_value() const
  {
    return m_value;
  }

private:
  std::string m_value;
}

// Modern idea when a copy is required
class MyClass
{
public:
  MyClass(std::string value)
    : m_value(std::move(value))
  {
  }

  std::string get_value() 
  {
    return m_value;
  }

private:
  std::string m_value;
}
```

## Prefer Stack Operations to Heap Operations

Heap operations have performance penalties in mulithreaded environments on most platforms and can possibly lead to memory errors if not used carefully.

Modern C++11 has special move operations which are designed to enhances the performance of stack based data by reducing or eliminating copies, which can bring even the single threaded case on par with heap based operations.

# References and Further Reading 
* [Original paper](https://gist.github.com/lefticus/10191322) by Jason Turner, @lefticus on [`github`](https://github.com/).
* This document is licensed under a [Creative Commons Attribution-NonCommercial 4.0 International License](https://creativecommons.org/licenses/by-nc/4.0/).
* Edited by Michael Itzhaki
* [C++ Best practices](https://github.com/lefticus/cppbestpractices)
