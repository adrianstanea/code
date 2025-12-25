add_library(SpreadSheet SHARED
    src/StringSpreadSheetCell.cpp
    src/DoubleSpreadSHeetCell.cpp
)
target_include_directories(SpreadSheet PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_executable(exercise-10-polymorphism
    main.cpp
)

# Link the app against the library target
target_link_libraries(exercise-10-polymorphism PRIVATE SpreadSheet)
