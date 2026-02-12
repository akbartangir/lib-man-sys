#include "gtest/gtest.h"
#include "library_manager.h"

class LibraryManagerTest : public ::testing::Test {
protected:
  LibraryManager manager;
};

// Test adding books
TEST_F(LibraryManagerTest, AddBook) {
  unsigned int id1 = manager.addBook("Book 1", "Author 1");
  unsigned int id2 = manager.addBook("Book 2", "Author 2");
  
  EXPECT_EQ(id1, 1);
  EXPECT_EQ(id2, 2);
  EXPECT_EQ(manager.getTotalBooks(), 2);
}

// Test getting book
TEST_F(LibraryManagerTest, GetBook) {
  unsigned int id = manager.addBook("Test Book", "Test Author", "123-456", 2024, "Fiction");
  
  auto book = manager.getBook(id);
  ASSERT_TRUE(book.has_value());
  EXPECT_EQ(book->getTitle(), "Test Book");
  EXPECT_EQ(book->getAuthor(), "Test Author");
  EXPECT_EQ(book->getISBN(), "123-456");
  EXPECT_EQ(book->getPublicationYear().value(), 2024);
  EXPECT_EQ(book->getCategory(), "Fiction");
}

// Test getting non-existent book
TEST_F(LibraryManagerTest, GetNonExistentBook) {
  auto book = manager.getBook(999);
  EXPECT_FALSE(book.has_value());
}

// Test removing book
TEST_F(LibraryManagerTest, RemoveBook) {
  unsigned int id = manager.addBook("Book to Remove", "Author");
  EXPECT_EQ(manager.getTotalBooks(), 1);
  
  bool removed = manager.removeBook(id);
  EXPECT_TRUE(removed);
  EXPECT_EQ(manager.getTotalBooks(), 0);
}

// Test removing non-existent book
TEST_F(LibraryManagerTest, RemoveNonExistentBook) {
  bool removed = manager.removeBook(999);
  EXPECT_FALSE(removed);
}

// Test updating book
TEST_F(LibraryManagerTest, UpdateBook) {
  unsigned int id = manager.addBook("Old Title", "Old Author");
  
  bool updated = manager.updateBook(id, "New Title", "New Author");
  EXPECT_TRUE(updated);
  
  auto book = manager.getBook(id);
  ASSERT_TRUE(book.has_value());
  EXPECT_EQ(book->getTitle(), "New Title");
  EXPECT_EQ(book->getAuthor(), "New Author");
}

// Test search by title
TEST_F(LibraryManagerTest, SearchByTitle) {
  manager.addBook("C++ Programming", "Author 1");
  manager.addBook("Python Programming", "Author 2");
  manager.addBook("C++ Advanced", "Author 3");
  
  auto results = manager.searchByTitle("C++");
  EXPECT_EQ(results.size(), 2);
}

// Test search by author
TEST_F(LibraryManagerTest, SearchByAuthor) {
  manager.addBook("Book 1", "John Smith");
  manager.addBook("Book 2", "Jane Doe");
  manager.addBook("Book 3", "John Doe");
  
  auto results = manager.searchByAuthor("John");
  EXPECT_EQ(results.size(), 2);
}

// Test search by category
TEST_F(LibraryManagerTest, SearchByCategory) {
  manager.addBook("Book 1", "Author 1", "", std::nullopt, "Fiction");
  manager.addBook("Book 2", "Author 2", "", std::nullopt, "Science");
  manager.addBook("Book 3", "Author 3", "", std::nullopt, "Fiction");
  
  auto results = manager.searchByCategory("Fiction");
  EXPECT_EQ(results.size(), 2);
}

// Test borrowing book
TEST_F(LibraryManagerTest, BorrowBook) {
  unsigned int id = manager.addBook("Book to Borrow", "Author");
  
  EXPECT_EQ(manager.getAvailableBooks(), 1);
  
  bool borrowed = manager.borrowBook(id);
  EXPECT_TRUE(borrowed);
  EXPECT_EQ(manager.getAvailableBooks(), 0);
  
  auto book = manager.getBook(id);
  ASSERT_TRUE(book.has_value());
  EXPECT_TRUE(book->isBorrowed());
}

// Test borrowing already borrowed book
TEST_F(LibraryManagerTest, BorrowAlreadyBorrowedBook) {
  unsigned int id = manager.addBook("Book", "Author");
  
  manager.borrowBook(id);
  bool borrowed_again = manager.borrowBook(id);
  
  EXPECT_FALSE(borrowed_again);
}

// Test returning book
TEST_F(LibraryManagerTest, ReturnBook) {
  unsigned int id = manager.addBook("Book to Return", "Author");
  manager.borrowBook(id);
  
  EXPECT_EQ(manager.getAvailableBooks(), 0);
  
  bool returned = manager.returnBook(id);
  EXPECT_TRUE(returned);
  EXPECT_EQ(manager.getAvailableBooks(), 1);
  
  auto book = manager.getBook(id);
  ASSERT_TRUE(book.has_value());
  EXPECT_TRUE(book->isAvailable());
}

// Test returning non-borrowed book
TEST_F(LibraryManagerTest, ReturnNonBorrowedBook) {
  unsigned int id = manager.addBook("Book", "Author");
  
  bool returned = manager.returnBook(id);
  EXPECT_FALSE(returned);
}

// Test getting all books
TEST_F(LibraryManagerTest, GetAllBooks) {
  manager.addBook("Book 1", "Author 1");
  manager.addBook("Book 2", "Author 2");
  manager.addBook("Book 3", "Author 3");
  
  auto books = manager.getAllBooks();
  EXPECT_EQ(books.size(), 3);
}

// Test statistics
TEST_F(LibraryManagerTest, Statistics) {
  unsigned int id1 = manager.addBook("Book 1", "Author 1");
  unsigned int id2 = manager.addBook("Book 2", "Author 2");
  unsigned int id3 = manager.addBook("Book 3", "Author 3");
  
  EXPECT_EQ(manager.getTotalBooks(), 3);
  EXPECT_EQ(manager.getAvailableBooks(), 3);
  
  manager.borrowBook(id1);
  manager.borrowBook(id2);
  
  EXPECT_EQ(manager.getTotalBooks(), 3);
  EXPECT_EQ(manager.getAvailableBooks(), 1);
}
