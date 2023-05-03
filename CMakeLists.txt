cmake_minimum_required(VERSION 3.11)

project(
  "ByeongJeon Highschool Dinner Checker"
  VERSION 0.1
  DESCRIPTION "This program is made for ByeongJeon Highschool"
  LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(tests)
