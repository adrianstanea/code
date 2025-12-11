cmake_minimum_required(VERSION 3.29)
project(std_module_example CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Compile commands exported to: ${CMAKE_BINARY_DIR}/compile_commands.json")
message(STATUS "")

add_subdirectory(cpp)
add_subdirectory(exploration)