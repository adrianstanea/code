#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'USAGE'
Usage: ./setup.sh <DayDir> <FileName>
Example: ./setup.sh D4 test.cpp
Example: ./setup.sh D6 math.cppm

This script:
 - creates src/<DayDir>/ directory
 - creates src/<DayDir>/<FileName> with appropriate C++23 template
 - .cpp files get a main() function with import std
 - .cppm files get a module export template
 - runs cmake configure to update compile_commands.json
 - builds the std_module target so clangd can use prebuilt std.pcm
USAGE
}

if [ "$#" -ne 2 ]; then
  usage
  exit 1
fi

DAYDIR="$1"
FILENAME="$2"

# Normalize paths
SRCDIR="src/${DAYDIR}"
FILEPATH="${SRCDIR}/${FILENAME}"

echo "📁 Creating directory: ${SRCDIR}"
mkdir -p "${SRCDIR}"

if [ -e "${FILEPATH}" ]; then
  echo "⚠️  File already exists: ${FILEPATH} - leaving it unchanged"
else
  echo "📄 Creating file: ${FILEPATH}"

  # Check file extension to determine template type
  case "${FILENAME}" in
    *.cppm)
      # Create a C++23 module template
      MODULE_NAME=$(basename "${FILENAME}" .cppm)
      cat > "${FILEPATH}" <<CPP
export module ${MODULE_NAME};

import std;

export {
  // Add your exported functions/variables here
  void hello_from_${MODULE_NAME}();
}

// Implementation (not exported)
void hello_from_${MODULE_NAME}() {
  std::print("Hello from ${MODULE_NAME} module in ${DAYDIR}!\n");
}
CPP
      ;;
    *.cpp)
      # Create a standard C++23 main program
      cat > "${FILEPATH}" <<CPP
import std;

int main() {
  std::println("Hello from ${DAYDIR}/${FILENAME}");
  return 0;
}
CPP
      ;;
    *)
      # Default to C++ for unknown extensions
      cat > "${FILEPATH}" <<CPP
import std;

int main() {
  std::println("Hello from ${DAYDIR}/${FILENAME}");
  return 0;
}
CPP
      ;;
  esac
fi

# Run CMake configure so compile_commands.json is updated for clangd
echo "🔧 Running CMake configure to update compile_commands.json"
cmake -B build -S . -DCMAKE_VERBOSE_MAKEFILE=ON

# Build std_module target so std.pcm and std.o exist for compile
echo "🏗️ Building std_module (prebuilt std)"
cmake --build build --target std_module --verbose

# Show status
echo "✅ Setup complete for ${DAYDIR}/${FILENAME}"
echo "🔎 You can now open the file in VS Code; clangd should pick up updated compile_commands.json."