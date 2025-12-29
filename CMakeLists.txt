cmake_minimum_required(VERSION 3.28...4.2)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

project(std_module_example LANGUAGES CXX)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed. Please create a separate build directory.")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(utils)

#
# Modules opt in only on compilers that support g++-15 and clang-20+
#
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 20)
    set(CMAKE_CXX_SCAN_FOR_MODULES 1)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 15)
    set(CMAKE_CXX_SCAN_FOR_MODULES 1)
else()
    set(CMAKE_CXX_SCAN_FOR_MODULES 0)
endif()


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# LLVM library
# add_compile_options(-stdlib=libc++)
# add_link_options(-stdlib=libc++)

# GNU library -> recommended on Linux since OS uses libstdc++
# add_compile_options(-stdlib=libstdc++)
# add_link_options(-stdlib=libstdc++)


message(STATUS "")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Compiler path: ${CMAKE_CXX_COMPILER}")
message(STATUS "Cmake: ${CMAKE_VERSION}")
message(STATUS "Modules support: ${CMAKE_CXX_SCAN_FOR_MODULES}")
message(STATUS "Compile commands exported to: ${CMAKE_BINARY_DIR}/compile_commands.json")
message(STATUS "")

add_subdirectory(cpp)
