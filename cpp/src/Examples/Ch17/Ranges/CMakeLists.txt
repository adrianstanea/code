add_executable(example-17-01-ranges)
target_sources(example-17-01-ranges
    PUBLIC
    main.cpp
)
# target_sources(example-17-01-ranges
#     PUBLIC
#     FILE_SET public_modules TYPE CXX_MODULES FILES
#     Person.cppm
#     PRIVATE
#     Person.cpp
# )

# set(CMAKE_CXX_MODULE_STD 1)
target_compile_features(example-17-01-ranges PRIVATE cxx_std_23)
set_target_properties(example-17-01-ranges PROPERTIES
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
    CXX_STANDARD_REQUIRED ON
    CXX_MODULE_STD ON
)
