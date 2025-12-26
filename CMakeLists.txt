cmake_minimum_required(VERSION 3.29)
project(std_module_example CXX)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed. Please create a separate build directory.")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-stdlib=libc++)
add_link_options(-stdlib=libc++)

message(STATUS "")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Compile commands exported to: ${CMAKE_BINARY_DIR}/compile_commands.json")
message(STATUS "")

add_subdirectory(cpp)
add_subdirectory(exploration)
