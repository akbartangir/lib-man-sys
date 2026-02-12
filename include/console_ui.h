
#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "library_manager.h"
#include <string>

class ConsoleUI {
public:
  explicit ConsoleUI(LibraryManager& manager);
  ~ConsoleUI() = default;

  void run();

private:
  LibraryManager& manager_;

  void displayMenu();
  void handleAddBook();
  void handleRemoveBook();
  void handleUpdateBook();
  void handleViewBook();
  void handleViewAllBooks();
  void handleSearchBooks();
  void handleBorrowBook();
  void handleReturnBook();
  void handleStatistics();
  
  void displayBook(const Book& book);
  std::string readLine(const std::string& prompt);
  int readInt(const std::string& prompt);
};

#endif // CONSOLE_UI_H
