add_executable(SpreadSheetApp main.cpp)

add_library(SpreadSheetCell)
target_sources(SpreadSheetCell
    PRIVATE
        SpreadSheetCell.cpp
    PUBLIC
        SpreadSheetCell.hpp
)

add_library(EvenSequence)
target_sources(EvenSequence
    PRIVATE
        EvenSequence.cpp
    PUBLIC
        EvenSequence.hpp
)

target_link_libraries(SpreadSheetApp PRIVATE SpreadSheetCell EvenSequence)
