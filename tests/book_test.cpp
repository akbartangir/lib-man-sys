#include "gtest/gtest.h"
#include "book.h"

// Test default constructor
TEST(BookTest, DefaultConstructor) {
  Book book;
  EXPECT_EQ(book.getBookID(), 0);
  EXPECT_TRUE(book.getTitle().empty());
  EXPECT_TRUE(book.getAuthor().empty());
  EXPECT_TRUE(book.isAvailable());
}

// Test parameterized constructor
TEST(BookTest, ParameterizedConstructor) {
  Book book(1, "Test Book", "Test Author", "123-456", 2024, "Fiction");
  
  EXPECT_EQ(book.getBookID(), 1);
  EXPECT_EQ(book.getTitle(), "Test Book");
  EXPECT_EQ(book.getAuthor(), "Test Author");
  EXPECT_EQ(book.getISBN(), "123-456");
  EXPECT_EQ(book.getPublicationYear().value(), 2024);
  EXPECT_EQ(book.getCategory(), "Fiction");
  EXPECT_TRUE(book.isAvailable());
}

// Test setters
TEST(BookTest, Setters) {
  Book book;
  
  book.setTitle("New Title");
  book.setAuthor("New Author");
  book.setISBN("999-888");
  book.setPublicationYear(2025);
  book.setCategory("Science");
  
  EXPECT_EQ(book.getTitle(), "New Title");
  EXPECT_EQ(book.getAuthor(), "New Author");
  EXPECT_EQ(book.getISBN(), "999-888");
  EXPECT_EQ(book.getPublicationYear().value(), 2025);
  EXPECT_EQ(book.getCategory(), "Science");
}

// Test status management
TEST(BookTest, StatusManagement) {
  Book book(1, "Test", "Author");
  
  EXPECT_EQ(book.getStatus(), BookStatus::Available);
  EXPECT_TRUE(book.isAvailable());
  EXPECT_FALSE(book.isBorrowed());
  
  book.setStatus(BookStatus::Borrowed);
  EXPECT_EQ(book.getStatus(), BookStatus::Borrowed);
  EXPECT_FALSE(book.isAvailable());
  EXPECT_TRUE(book.isBorrowed());
  
  book.setStatus(BookStatus::Reserved);
  EXPECT_EQ(book.getStatus(), BookStatus::Reserved);
  EXPECT_FALSE(book.isAvailable());
  EXPECT_FALSE(book.isBorrowed());
}

// Test copy constructor
TEST(BookTest, CopyConstructor) {
  Book original(1, "Original Title", "Original Author", "111-222", 2020, "History");
  Book copy(original);
  
  EXPECT_EQ(copy.getBookID(), original.getBookID());
  EXPECT_EQ(copy.getTitle(), original.getTitle());
  EXPECT_EQ(copy.getAuthor(), original.getAuthor());
  EXPECT_EQ(copy.getISBN(), original.getISBN());
  EXPECT_EQ(copy.getPublicationYear(), original.getPublicationYear());
  EXPECT_EQ(copy.getCategory(), original.getCategory());
}

// Test move constructor
TEST(BookTest, MoveConstructor) {
  Book original(1, "Original Title", "Original Author");
  std::string original_title = original.getTitle();
  
  Book moved(std::move(original));
  
  EXPECT_EQ(moved.getBookID(), 1);
  EXPECT_EQ(moved.getTitle(), original_title);
  EXPECT_EQ(moved.getAuthor(), "Original Author");
}

// Test optional publication year
TEST(BookTest, OptionalPublicationYear) {
  Book book1(1, "Book Without Year", "Author");
  EXPECT_FALSE(book1.getPublicationYear().has_value());
  
  Book book2(2, "Book With Year", "Author", "", 2023);
  EXPECT_TRUE(book2.getPublicationYear().has_value());
  EXPECT_EQ(book2.getPublicationYear().value(), 2023);
}
