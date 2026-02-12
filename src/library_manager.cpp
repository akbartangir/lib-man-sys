#include "../include/library_manager.h"
#include <algorithm>

unsigned int LibraryManager::addBook(std::string_view title, 
                                      std::string_view author,
                                      std::string_view isbn,
                                      std::optional<unsigned int> publication_year,
                                      std::string_view category) {
  unsigned int book_id = next_book_id_++;
  Book book(book_id, title, author, isbn, publication_year, category);
  books_[book_id] = std::move(book);
  return book_id;
}

bool LibraryManager::removeBook(unsigned int book_id) {
  return books_.erase(book_id) > 0;
}

bool LibraryManager::updateBook(unsigned int book_id, 
                                 std::string_view title, 
                                 std::string_view author) {
  auto it = books_.find(book_id);
  if (it == books_.end()) {
    return false;
  }
  
  it->second.setTitle(title);
  it->second.setAuthor(author);
  return true;
}

std::optional<Book> LibraryManager::getBook(unsigned int book_id) const {
  auto it = books_.find(book_id);
  if (it == books_.end()) {
    return std::nullopt;
  }
  return it->second;
}

std::vector<Book> LibraryManager::getAllBooks() const {
  std::vector<Book> result;
  result.reserve(books_.size());
  
  for (const auto& [id, book] : books_) {
    result.push_back(book);
  }
  
  return result;
}

std::vector<Book> LibraryManager::searchByTitle(std::string_view title) const {
  std::vector<Book> result;
  
  for (const auto& [id, book] : books_) {
    if (book.getTitle().find(title) != std::string::npos) {
      result.push_back(book);
    }
  }
  
  return result;
}

std::vector<Book> LibraryManager::searchByAuthor(std::string_view author) const {
  std::vector<Book> result;
  
  for (const auto& [id, book] : books_) {
    if (book.getAuthor().find(author) != std::string::npos) {
      result.push_back(book);
    }
  }
  
  return result;
}

std::vector<Book> LibraryManager::searchByCategory(std::string_view category) const {
  std::vector<Book> result;
  
  for (const auto& [id, book] : books_) {
    if (book.getCategory() == category) {
      result.push_back(book);
    }
  }
  
  return result;
}

bool LibraryManager::borrowBook(unsigned int book_id) {
  auto it = books_.find(book_id);
  if (it == books_.end() || !it->second.isAvailable()) {
    return false;
  }
  
  it->second.setStatus(BookStatus::Borrowed);
  return true;
}

bool LibraryManager::returnBook(unsigned int book_id) {
  auto it = books_.find(book_id);
  if (it == books_.end() || !it->second.isBorrowed()) {
    return false;
  }
  
  it->second.setStatus(BookStatus::Available);
  return true;
}

size_t LibraryManager::getTotalBooks() const {
  return books_.size();
}

size_t LibraryManager::getAvailableBooks() const {
  return std::count_if(books_.begin(), books_.end(), 
                       [](const auto& pair) { 
                         return pair.second.isAvailable(); 
                       });
}
