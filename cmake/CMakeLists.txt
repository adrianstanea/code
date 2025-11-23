cmake_minimum_required(VERSION 4.0.0)

project(Tutorial VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_MY_MATH
    "Wether to use the tutorial provided math function implementations."
    ON
)

configure_file(
    ${CMAKE_SOURCE_DIR}/TutorialConfig.h.in
    ${CMAKE_BINARY_DIR}/TutorialConfig.h
)

if(USE_MY_MATH)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/MathFunctions)
    add_subdirectory(MathFunctions)
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MY_MATH)


add_executable(Tutorial tutorial.cxx)

target_include_directories(Tutorial
    # Add the binary directory to the search path for include files to locate the Config header file
    PUBLIC ${PROJECT_BINARY_DIR}
)
target_link_libraries(Tutorial PUBLIC "${EXTRA_LIIBS}")
