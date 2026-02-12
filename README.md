# Library Management System

A modern C++23 library management system with clean architecture and comprehensive testing.

## Features

- **Book Management**: Add, remove, update, and view books
- **Search Functionality**: Search by title, author, or category
- **Borrow/Return System**: Track book availability and borrowing
- **Statistics**: View library statistics
- **Interactive UI**: User-friendly console interface

## Architecture

The system follows a clean three-layer architecture:

- **Model Layer** (`Book`): Pure data model with modern C++ features
- **Service Layer** (`LibraryManager`): Business logic and operations
- **Presentation Layer** (`ConsoleUI`): User interaction

## Modern C++ Features

- C++23 `std::print` and `std::println`
- `std::optional` for nullable fields
- `std::string_view` for zero-copy string passing
- `enum class` for type safety
- `[[nodiscard]]` attributes
- Move semantics
- Const correctness throughout

## Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Running

```bash
./lms
```

## Testing

The project includes comprehensive unit tests using GoogleTest:

```bash
./unit_tests
```

All 23 tests cover:
- Book construction and manipulation
- Status management
- CRUD operations
- Search functionality
- Borrow/Return workflows

## Requirements

- CMake 3.20 or higher
- C++23 compatible compiler (GCC 13+, Clang 16+, MSVC 19.34+)
