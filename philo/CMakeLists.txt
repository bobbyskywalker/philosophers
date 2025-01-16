cmake_minimum_required(VERSION 3.10)

# Set project name and language (C and C++)
project(philo C CXX)

# Specify the C and C++ compilers explicitly (if needed)
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# Specify C++ include directories (make sure to use the correct version you have installed)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include/c++/12")

# Enable testing
enable_testing()

# Add GoogleTest to the project (from the 'tests/googletest' directory)
add_subdirectory(tests/googletest)

# Include directories for source and header files
# You can use target_include_directories for better control over the scope of the include directories
include_directories(src inc)

# Create a library from your C source files (no need to use file names as target names)
add_library(error_handler
    src/error_handler.c
    src/utils.c
)

# Create the test executable from C test file
add_executable(run_tests tests/error_handler_test.c)

# Link the GoogleTest and your C code
target_link_libraries(run_tests gtest gtest_main error_handler)

# Register tests with GoogleTest
include(GoogleTest)
gtest_discover_tests(run_tests)
