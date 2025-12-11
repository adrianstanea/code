# 🎓 Educational C++23 Learning Environment with Clang-19 Modules
# This CMakeLists.txt is designed for learning - every command is explained!

# 📋 Minimum CMake version required for C++23 module support
cmake_minimum_required(VERSION 3.28)

# 🔧 CRITICAL: Set compiler and libc++ BEFORE project() call
# This ensures CMake's compiler tests use the correct standard library
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-19")
set(CMAKE_C_COMPILER "/usr/bin/clang-19")

# 🎯 Force libc++ instead of libstdc++ for C++23 modules
set(CMAKE_CXX_FLAGS "-stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libc++")

# 🎯 Project definition - this creates the overall project scope
project(cpp-refresher
    VERSION 1.0.0
    DESCRIPTION "Daily C++ Learning with C++23 Modules"
    LANGUAGES CXX
)

# 🔧 Compiler Configuration - Teaching you what each flag does
message(STATUS "📚 Learning Mode: Configuring C++23 with Clang-19...")
message(STATUS "🔧 Using Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "🎯 Using Standard Library: libc++")

# 🎯 C++ Standard Configuration
set(CMAKE_CXX_STANDARD 23)              # Use C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Fail if C++23 not available
set(CMAKE_CXX_EXTENSIONS OFF)           # Use pure C++23, not GNU extensions

# 📝 Learning Feature: Export compile commands for clangd IntelliSense
# This creates compile_commands.json that clangd uses to understand your code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 🎨 Build Configuration for Learning
set(CMAKE_BUILD_TYPE Debug)             # Full debug symbols for learning
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")     # No optimization, full debugging info

# 🔍 Verbose Build Output - You'll see every command that runs!
set(CMAKE_VERBOSE_MAKEFILE ON)

# 📚 C++23 Module Configuration
# These settings enable experimental C++23 module support
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

# 🏗️ Global Module Cache Directory
# This is where our std.pcm will be stored and shared across all days
set(CMAKE_CXX_MODULE_BMI_DIRECTORY "${CMAKE_BINARY_DIR}/modules")
file(MAKE_DIRECTORY "${CMAKE_CXX_MODULE_BMI_DIRECTORY}")

# 🎯 Additional Clang-specific flags for C++23 modules
# Note: -stdlib=libc++ is already set globally above
add_compile_options(
    "-fprebuilt-module-path=${CMAKE_BINARY_DIR}/modules"  # Where to find .pcm files
)

#  Function to build any daily C++ file with full educational output
function(build_daily_cpp DAY_DIR CPP_FILE)
    # Extract filename without extension for the executable name
    get_filename_component(EXEC_NAME ${CPP_FILE} NAME_WE)

    # Create a unique target name for this day
    set(TARGET_NAME "${DAY_DIR}_${EXEC_NAME}")

    message(STATUS "🎯 Setting up build for Day ${DAY_DIR}: ${CPP_FILE}")
    message(STATUS "📋 Target: ${TARGET_NAME}")
    message(STATUS "💻 Executable: ${EXEC_NAME}")

    # Create executable target
    add_executable(${TARGET_NAME} ${CPP_FILE})

    # Set output directory to the day's build folder
    set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/src/${DAY_DIR}/build"
        OUTPUT_NAME ${EXEC_NAME}
    )

    # Add C++23 module support if the file uses 'import std;'
    file(READ ${CPP_FILE} FILE_CONTENT)
    if(FILE_CONTENT MATCHES "import std")
        message(STATUS "🎓 Detected 'import std;' - enabling C++23 module support")

        # This target depends on the std module being built
        target_compile_features(${TARGET_NAME} PRIVATE cxx_std_23)

        # Add module-specific compile flags
        target_compile_options(${TARGET_NAME} PRIVATE
            "-fmodule-file=std=${CMAKE_CXX_MODULE_BMI_DIRECTORY}/std.pcm"
        )

        # Link with the std module object file
        target_link_libraries(${TARGET_NAME} "${CMAKE_CXX_MODULE_BMI_DIRECTORY}/std.o")
    endif()

    message(STATUS "✅ ${DAY_DIR}/${CPP_FILE} configured for building")
endfunction()

# 🎯 Auto-discover and configure all daily learning files
# This scans your src/ directory and sets up builds for each day
file(GLOB_RECURSE CPP_FILES "src/D*/*.cpp")

foreach(CPP_FILE ${CPP_FILES})
    # Extract day directory (D1, D2, D3, etc.)
    string(REGEX MATCH "src/(D[0-9]+)/" MATCH_RESULT ${CPP_FILE})
    if(CMAKE_MATCH_1)
        set(DAY_DIR ${CMAKE_MATCH_1})
        build_daily_cpp(${DAY_DIR} ${CPP_FILE})
    endif()
endforeach()

# 📋 Custom targets for building the C++23 std module
# This is the educational part - you'll see exactly how modules are built!

add_custom_command(
    OUTPUT "${CMAKE_CXX_MODULE_BMI_DIRECTORY}/std.pcm" "${CMAKE_CXX_MODULE_BMI_DIRECTORY}/std.o"
    COMMAND ${CMAKE_COMMAND} -E echo "🎓 LEARNING: Building C++23 std module with full command visibility..."
    COMMAND ${CMAKE_COMMAND} -E echo "📝 Command: clang++-19 -std=c++23 -stdlib=libc++ --precompile -o std.pcm /usr/lib/llvm-19/share/libc++/v1/std.cppm"
    COMMAND clang++-19 -std=c++23 -stdlib=libc++ --precompile -o std.pcm /usr/lib/llvm-19/share/libc++/v1/std.cppm
    COMMAND ${CMAKE_COMMAND} -E echo "📝 Command: clang++-19 -std=c++23 -stdlib=libc++ -c std.pcm -o std.o"
    COMMAND clang++-19 -std=c++23 -stdlib=libc++ -c std.pcm -o std.o
    COMMAND ${CMAKE_COMMAND} -E echo "✅ C++23 std module built successfully!"
    WORKING_DIRECTORY "${CMAKE_CXX_MODULE_BMI_DIRECTORY}"
    DEPENDS "/usr/lib/llvm-19/share/libc++/v1/std.cppm"
    COMMENT "🏗️ Building C++23 std module for learning environment"
)

# Create a target for the std module
add_custom_target(std_module
    DEPENDS "${CMAKE_CXX_MODULE_BMI_DIRECTORY}/std.pcm" "${CMAKE_CXX_MODULE_BMI_DIRECTORY}/std.o"
)

# 🎯 Educational summary
message(STATUS "")
message(STATUS "🎓 C++23 Learning Environment Configured!")
message(STATUS "📋 Found C++ files: ${CPP_FILES}")
message(STATUS "🔧 Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "🎯 Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "📝 Compile commands will be exported to: ${CMAKE_BINARY_DIR}/compile_commands.json")
message(STATUS "🏗️ Module cache directory: ${CMAKE_CXX_MODULE_BMI_DIRECTORY}")
message(STATUS "")
message(STATUS "🚀 Ready for daily C++ learning!")
message(STATUS "💡 Use 'cmake --build build --verbose' to see full compilation commands")
message(STATUS "")