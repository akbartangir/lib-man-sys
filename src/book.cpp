#include "../include/book.h"

Book::Book(unsigned int book_id,
           std::string_view title,
           std::string_view author,
           std::string_view isbn,
           std::optional<unsigned int> publication_year,
           std::string_view category)
    : book_id_(book_id), title_(title), author_(author), isbn_(isbn),
      publication_year_(publication_year), category_(category), status_(BookStatus::Available) {
}

// Setters
void Book::setTitle(std::string_view title) {
  title_ = title;
}

void Book::setAuthor(std::string_view author) {
  author_ = author;
}

void Book::setISBN(std::string_view isbn) {
  isbn_ = isbn;
}

void Book::setPublicationYear(unsigned int year) {
  publication_year_ = year;
}

void Book::setCategory(std::string_view category) {
  category_ = category;
}

void Book::setStatus(BookStatus status) {
  status_ = status;
}

// Getters
unsigned int Book::getBookID() const {
  return book_id_;
}

const std::string& Book::getTitle() const {
  return title_;
}

const std::string& Book::getAuthor() const {
  return author_;
}

const std::string& Book::getISBN() const {
  return isbn_;
}

std::optional<unsigned int> Book::getPublicationYear() const {
  return publication_year_;
}

const std::string& Book::getCategory() const {
  return category_;
}

BookStatus Book::getStatus() const {
  return status_;
}

// Status helpers
bool Book::isAvailable() const {
  return status_ == BookStatus::Available;
}

bool Book::isBorrowed() const {
  return status_ == BookStatus::Borrowed;
}
