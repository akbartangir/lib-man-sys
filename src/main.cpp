#include "console_ui.h"
#include "library_manager.h"

#include <print>

auto main() -> int {
  std::println("Library Management System v0.1\n");

  LibraryManager manager;
  ConsoleUI ui(manager);

  manager.addBook(
      "The C++ Programming Language", "Bjarne Stroustrup", "978-0321563842", 2013, "Programming");
  manager.addBook("Effective Modern C++", "Scott Meyers", "978-1491903995", 2014, "Programming");
  manager.addBook(
      "Design Patterns", "Gang of Four", "978-0201633610", 1994, "Software Engineering");

  ui.run();

  return 0;
}
