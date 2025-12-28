option(WITH_LOGS "Enable logging" OFF)

add_executable(example-14-02-source-location main.cpp)

target_include_directories(example-14-02-source-location PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(WITH_LOGS)
    target_compile_definitions(example-14-02-source-location PUBLIC WITH_LOGS)
endif()
