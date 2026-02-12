
#ifndef BOOK_H
#define BOOK_H

#include <optional>
#include <string>
#include <string_view>

enum class BookStatus { Available, Borrowed, Reserved, UnderMaintenance };

class Book {
public:
  Book() = default;
  Book(unsigned int book_id,
       std::string_view title,
       std::string_view author,
       std::string_view isbn = "",
       std::optional<unsigned int> publication_year = std::nullopt,
       std::string_view category = "General");

  ~Book() = default;

  // Copy semantics
  Book(const Book&) = default;
  Book& operator=(const Book&) = default;

  // Move semantics
  Book(Book&&) noexcept = default;
  Book& operator=(Book&&) noexcept = default;

  // Setters
  void setTitle(std::string_view title);
  void setAuthor(std::string_view author);
  void setISBN(std::string_view isbn);
  void setPublicationYear(unsigned int year);
  void setCategory(std::string_view category);
  void setStatus(BookStatus status);

  // Getters
  [[nodiscard]] unsigned int getBookID() const;
  [[nodiscard]] const std::string& getTitle() const;
  [[nodiscard]] const std::string& getAuthor() const;
  [[nodiscard]] const std::string& getISBN() const;
  [[nodiscard]] std::optional<unsigned int> getPublicationYear() const;
  [[nodiscard]] const std::string& getCategory() const;
  [[nodiscard]] BookStatus getStatus() const;

  // Status helpers
  [[nodiscard]] bool isAvailable() const;
  [[nodiscard]] bool isBorrowed() const;

private:
  unsigned int book_id_{0};
  std::string title_;
  std::string author_;
  std::string isbn_;
  std::optional<unsigned int> publication_year_;
  std::string category_;
  BookStatus status_{BookStatus::Available};
};

#endif // BOOK_H
