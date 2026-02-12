cmake_minimum_required(VERSION 3.20)
project("Library Management System" VERSION 0.1)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------
# Application
# ------------------------
add_executable(lms 
    src/main.cpp 
    src/book.cpp
    src/student.cpp
    src/library_manager.cpp
    src/console_ui.cpp
)
target_include_directories(lms PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ------------------------
# GoogleTest
# ------------------------
include(FetchContent)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For MSVC shared CRT issues (harmless on non-MSVC)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Build a single test runner that picks up all test files automatically
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")
add_executable(unit_tests 
    ${TEST_SOURCES}
    src/book.cpp
    src/library_manager.cpp
)
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

add_test(NAME unit_tests COMMAND unit_tests)

# Print project configuration
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
