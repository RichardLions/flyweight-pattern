# Flyweight Pattern

This pattern was inspired by [Game Programming Patterns](https://gameprogrammingpatterns.com/flyweight.html).

## When To Use

This pattern allows any kind of immutable data(flyweight) to be shared between many objects.

General:
* Decouples the lifetime management of the flyweight from the objects sharing the flyweight.
* Reduce memory usage by objects referencing a flyweight.

Implementation Considerations:
* Will all flyweights be preloaded? Resulting in an error if no flyweight can be found for an identifier.
* Support on demand flyweight creation? Will the call be blocking? Or use an asynchronous pattern such as future/promise?
* Should the factory periodically check for unreferenced flyweights and remove them?
* Should objects inform the factory when they no longer reference a flyweight directly?
* Should the factory be able to clear all flyweights independently of the lifetime of the objects sharing the flyweights?

## Features

Create a flyweight factory and get/create a flyweight:
```cpp
class FlyweightType
{
    ...
};

FlyweightFactory<FlyweightType> factory{};


std::shared_ptr<const FlyweightType> flyweight{factory.GetFlyweight("Flyweight Identifier")};
```

## Setup

This repository uses the .sln/.proj files created by Visual Studio 2022 Community Edition.
Using MSVC compiler, Preview version(C++23 Preview). 

### Catch2
The examples for how to use the pattern are written as Unit Tests.

Launching the program in Debug or Release will run the Unit Tests.

Alternative:
Installing the Test Adapter for Catch2 Visual Studio extension enables running the Unit Tests via the Test Explorer Window. Setup the Test Explorer to use the project's .runsettings file.

### vcpkg
This repository uses vcpkg in manifest mode for it's dependencies. To interact with vcpkg, open a Developer PowerShell (View -> Terminal).

To setup vcpkg, install it via the Visual Studio installer. To enable/disable it run these commands from the Developer PowerShell:
```
vcpkg integrate install
vcpkg integrate remove
```

To add additional dependencies run:
```
vcpkg add port [dependency name]
```

To update the version of a dependency modify the overrides section of vcpkg.json. 

To create a clean vcpkg.json and vcpkg-configuration.json file run:
```
vcpkg new --application
```

### TODO
- [x] Implementation
- [x] Unit Tests
- [x] Benchmarks
