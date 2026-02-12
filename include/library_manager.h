
#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H

#include "book.h"
#include <memory>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>

class LibraryManager {
public:
  LibraryManager() = default;
  ~LibraryManager() = default;

  // Book management
  [[nodiscard]] unsigned int addBook(std::string_view title, 
                                      std::string_view author,
                                      std::string_view isbn = "",
                                      std::optional<unsigned int> publication_year = std::nullopt,
                                      std::string_view category = "General");
  
  [[nodiscard]] bool removeBook(unsigned int book_id);
  [[nodiscard]] bool updateBook(unsigned int book_id, 
                                 std::string_view title, 
                                 std::string_view author);
  
  [[nodiscard]] std::optional<Book> getBook(unsigned int book_id) const;
  [[nodiscard]] std::vector<Book> getAllBooks() const;
  
  // Search operations
  [[nodiscard]] std::vector<Book> searchByTitle(std::string_view title) const;
  [[nodiscard]] std::vector<Book> searchByAuthor(std::string_view author) const;
  [[nodiscard]] std::vector<Book> searchByCategory(std::string_view category) const;
  
  // Borrow/Return operations
  [[nodiscard]] bool borrowBook(unsigned int book_id);
  [[nodiscard]] bool returnBook(unsigned int book_id);
  
  [[nodiscard]] size_t getTotalBooks() const;
  [[nodiscard]] size_t getAvailableBooks() const;

private:
  std::unordered_map<unsigned int, Book> books_;
  unsigned int next_book_id_{1};
};

#endif // LIBRARY_MANAGER_H
