add_executable(example-11-private-module-fragments)
target_sources(example-11-private-module-fragments
    PUBLIC
    main.cpp
)
target_sources(example-11-private-module-fragments
    PUBLIC
    FILE_SET public_modules TYPE CXX_MODULES FILES
    adder.cppm
    # PRIVATE
    # Person.cpp
)

# set(CMAKE_CXX_MODULE_STD 1)
target_compile_features(example-11-private-module-fragments PRIVATE cxx_std_23)
set_target_properties(example-11-private-module-fragments PROPERTIES
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
    CXX_STANDARD_REQUIRED ON
    CXX_MODULE_STD ON
)
