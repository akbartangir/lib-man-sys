#include "../include/console_ui.h"

#include <iostream>
#include <limits>
#include <print>

ConsoleUI::ConsoleUI(LibraryManager& manager) : manager_(manager) {
}

void ConsoleUI::run() {
  while (true) {
    displayMenu();
    int choice = readInt("Enter your choice: ");

    std::println(""); // Blank line for readability

    switch (choice) {
    case 1:
      handleAddBook();
      break;
    case 2:
      handleRemoveBook();
      break;
    case 3:
      handleUpdateBook();
      break;
    case 4:
      handleViewBook();
      break;
    case 5:
      handleViewAllBooks();
      break;
    case 6:
      handleSearchBooks();
      break;
    case 7:
      handleBorrowBook();
      break;
    case 8:
      handleReturnBook();
      break;
    case 9:
      handleStatistics();
      break;
    case 0:
      std::println("Thank you for using the Library Management System!");
      return;
    default:
      std::println("Invalid choice! Please try again.");
    }

    std::println("\nPress Enter to continue...");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
  }
}

void ConsoleUI::displayMenu() {
  std::println("");
  std::println("╔════════════════════════════════════════╗");
  std::println("║  LIBRARY MANAGEMENT SYSTEM             ║");
  std::println("╠════════════════════════════════════════╣");
  std::println("║  1. Add Book                           ║");
  std::println("║  2. Remove Book                        ║");
  std::println("║  3. Update Book                        ║");
  std::println("║  4. View Book Details                  ║");
  std::println("║  5. View All Books                     ║");
  std::println("║  6. Search Books                       ║");
  std::println("║  7. Borrow Book                        ║");
  std::println("║  8. Return Book                        ║");
  std::println("║  9. View Statistics                    ║");
  std::println("║  0. Exit                               ║");
  std::println("╚════════════════════════════════════════╝");
}

void ConsoleUI::handleAddBook() {
  std::println("=== ADD NEW BOOK ===");

  std::string title = readLine("Enter book title: ");
  std::string author = readLine("Enter author: ");
  std::string isbn = readLine("Enter ISBN (optional): ");

  std::print("Enter publication year (0 to skip): ");
  int year = readInt("");
  std::optional<unsigned int> pub_year =
      (year > 0) ? std::optional<unsigned int>(year) : std::nullopt;

  std::string category = readLine("Enter category (default: General): ");
  if (category.empty()) {
    category = "General";
  }

  unsigned int book_id = manager_.addBook(title, author, isbn, pub_year, category);
  std::println("\n✓ Book added successfully! Book ID: {}", book_id);
}

void ConsoleUI::handleRemoveBook() {
  std::println("=== REMOVE BOOK ===");

  int book_id = readInt("Enter book ID to remove: ");

  if (manager_.removeBook(book_id)) {
    std::println("\n✓ Book removed successfully!");
  } else {
    std::println("\n✗ Book not found!");
  }
}

void ConsoleUI::handleUpdateBook() {
  std::println("=== UPDATE BOOK ===");

  int book_id = readInt("Enter book ID to update: ");

  auto book = manager_.getBook(book_id);
  if (!book) {
    std::println("\n✗ Book not found!");
    return;
  }

  std::println("\nCurrent details:");
  displayBook(*book);

  std::string title = readLine("\nEnter new title (or press Enter to keep current): ");
  std::string author = readLine("Enter new author (or press Enter to keep current): ");

  if (title.empty())
    title = book->getTitle();
  if (author.empty())
    author = book->getAuthor();

  if (manager_.updateBook(book_id, title, author)) {
    std::println("\n✓ Book updated successfully!");
  } else {
    std::println("\n✗ Failed to update book!");
  }
}

void ConsoleUI::handleViewBook() {
  std::println("=== VIEW BOOK DETAILS ===");

  int book_id = readInt("Enter book ID: ");

  auto book = manager_.getBook(book_id);
  if (book) {
    std::println("");
    displayBook(*book);
  } else {
    std::println("\n✗ Book not found!");
  }
}

void ConsoleUI::handleViewAllBooks() {
  std::println("=== ALL BOOKS ===\n");

  auto books = manager_.getAllBooks();

  if (books.empty()) {
    std::println("No books in the library.");
    return;
  }

  for (const auto& book : books) {
    displayBook(book);
    std::println("─────────────────────────────────────────");
  }

  std::println("\nTotal books: {}", books.size());
}

void ConsoleUI::handleSearchBooks() {
  std::println("=== SEARCH BOOKS ===");
  std::println("1. Search by title");
  std::println("2. Search by author");
  std::println("3. Search by category");

  int choice = readInt("\nEnter your choice: ");
  std::vector<Book> results;

  switch (choice) {
  case 1: {
    std::string title = readLine("Enter title to search: ");
    results = manager_.searchByTitle(title);
    break;
  }
  case 2: {
    std::string author = readLine("Enter author to search: ");
    results = manager_.searchByAuthor(author);
    break;
  }
  case 3: {
    std::string category = readLine("Enter category to search: ");
    results = manager_.searchByCategory(category);
    break;
  }
  default:
    std::println("Invalid choice!");
    return;
  }

  std::println("\n=== SEARCH RESULTS ===");
  if (results.empty()) {
    std::println("No books found.");
  } else {
    for (const auto& book : results) {
      displayBook(book);
      std::println("─────────────────────────────────────────");
    }
    std::println("\nFound {} book(s).", results.size());
  }
}

void ConsoleUI::handleBorrowBook() {
  std::println("=== BORROW BOOK ===");

  int book_id = readInt("Enter book ID to borrow: ");

  if (manager_.borrowBook(book_id)) {
    std::println("\n✓ Book borrowed successfully!");
  } else {
    std::println("\n✗ Book not available for borrowing!");
  }
}

void ConsoleUI::handleReturnBook() {
  std::println("=== RETURN BOOK ===");

  int book_id = readInt("Enter book ID to return: ");

  if (manager_.returnBook(book_id)) {
    std::println("\n✓ Book returned successfully!");
  } else {
    std::println("\n✗ Book was not borrowed or not found!");
  }
}

void ConsoleUI::handleStatistics() {
  std::println("=== LIBRARY STATISTICS ===");
  std::println("Total books:     {}", manager_.getTotalBooks());
  std::println("Available books: {}", manager_.getAvailableBooks());
  std::println("Borrowed books:  {}", manager_.getTotalBooks() - manager_.getAvailableBooks());
}

void ConsoleUI::displayBook(const Book& book) {
  std::println("Book ID:    {}", book.getBookID());
  std::println("Title:      {}", book.getTitle());
  std::println("Author:     {}", book.getAuthor());

  if (!book.getISBN().empty()) {
    std::println("ISBN:       {}", book.getISBN());
  }

  if (book.getPublicationYear()) {
    std::println("Year:       {}", *book.getPublicationYear());
  }

  std::println("Category:   {}", book.getCategory());

  std::string status;
  switch (book.getStatus()) {
  case BookStatus::Available:
    status = "Available";
    break;
  case BookStatus::Borrowed:
    status = "Borrowed";
    break;
  case BookStatus::Reserved:
    status = "Reserved";
    break;
  case BookStatus::UnderMaintenance:
    status = "Under Maintenance";
    break;
  }
  std::println("Status:     {}", status);
}

std::string ConsoleUI::readLine(const std::string& prompt) {
  std::print("{}", prompt);
  std::string line;
  std::getline(std::cin, line);
  return line;
}

int ConsoleUI::readInt(const std::string& prompt) {
  std::print("{}", prompt);
  int value;

  while (!(std::cin >> value)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::print("Invalid input! Please enter a number: ");
  }

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return value;
}
