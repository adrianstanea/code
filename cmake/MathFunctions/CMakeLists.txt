# add the library that runs the math functions
add_library(MathFunctions MathFunctions.cxx)

# Here we state that anybody linking to MathFunctions needs
# to include the current source directory to find the headers (MathFunctions.h)
target_include_directories(MathFunctions
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}
    $<INSTALL_INTERFACE:include>
)

option(USE_MY_MATH
    "Wether to use the tutorial provided math function implementations."
    ON
)

if(USE_MY_MATH)
    include(CheckSymbolExists)
    set(CMAKE_REQUIRED_LIBRARIES "m")
    check_symbol_exists(log "math.h" HAVE_LOG)
    check_symbol_exists(exp "math.h" HAVE_EXP)

    # First add the executable that generates the table
    add_executable(MakeTable MakeTable.cxx)

    # Add the command to generate the table before building the library
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        DEPENDS MakeTable # MakeTable must be built before running this command
    )

    # Add a library that just does sqr
    add_library(SqrtLibrary STATIC
        mysqrt.cxx
        ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    )

    # State that we depend on our binary dir to find the Table.h file
    target_include_directories(SqrtLibrary PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
    )

    # set_target_properties(SqrtLibrary PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

    target_compile_definitions(SqrtLibrary PRIVATE
        "$<$<BOOL:${HAVE_LOG}>:HAVE_LOG>"
        "$<$<BOOL:${HAVE_EXP}>:HAVE_EXP>"
    )

    target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif(USE_MY_MATH)

target_compile_definitions(MathFunctions PRIVATE
    "$<$<BOOL:${USE_MY_MATH}>:USE_MY_MATH>"
)

# Define symbol stating we are using the declspec(dllexport) when building the library on Windows
target_compile_definitions(MathFunctions PRIVATE
    "EXPORTING_MY_MATH"
)

# Setup the Version Numbering
set_property(TARGET MathFunctions PROPERTY VERSION "1.0.0")
set_property(TARGET MathFunctions PROPERTY SOVERSION "1")

install(TARGETS MathFunctions
    DESTINATION lib
    EXPORT MathFunctionsTargets
)
install(FILES MathFunctions.h DESTINATION include)
