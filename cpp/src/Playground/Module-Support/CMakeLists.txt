add_executable(playground-module-setup)
target_sources(playground-module-setup
    PUBLIC
    main.cpp
)
target_sources(playground-module-setup
    PUBLIC
    FILE_SET all_my_modules TYPE CXX_MODULES
    FILES
    a.cppm
)

# set(CMAKE_CXX_MODULE_STD 1)
target_compile_features(playground-module-setup PRIVATE cxx_std_23)
set_target_properties(playground-module-setup PROPERTIES
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
    CXX_STANDARD_REQUIRED ON
    CXX_MODULE_STD ON
)
