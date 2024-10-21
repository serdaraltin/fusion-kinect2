cmake_minimum_required(VERSION 3.29)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

#------------------------------- PROJECT SETUP -------------------------------

# Define project name
project(fusion_vision)

# Find necessary packages
find_package(OpenCV REQUIRED)        # OpenCV for computer vision functionalities
find_package(Boost 1.86.0 REQUIRED)

# Add include directories (for headers and external libraries)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include  # Custom include directory
        ${CMAKE_CURRENT_SOURCE_DIR}/lib      # Custom libraries directory
        ${OpenCV_INCLUDE_DIRS}               # OpenCV include directories
        ${Boost_INCLUDE_DIRS}
)

#------------------------------- FILE GLOBBING -------------------------------

# Recursively gather all source, header, and test files
file(GLOB_RECURSE HEADER_SOURCE "include/**/*.h")  # Header files in include/
file(GLOB_RECURSE MAIN_SOURCE "src/**/*.cpp")      # Source files in src/
file(GLOB_RECURSE TEST_SOURCE "test/*.cpp")    # Test files in tests/
file(GLOB_RECURSE LIB_SOURCE "lib/**/*.h")         # Library headers in lib/

# Main application entry point
set(MAIN_FILE src/main.cpp)

# Output status messages for debugging
message(STATUS "Source files: ${MAIN_SOURCE}")
message(STATUS "Test files: ${TEST_SOURCE}")
message(STATUS "Header files: ${HEADER_SOURCE}")
message(STATUS "OpenCV files: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "Boost files: ${Boost_INCLUDE_DIRS}")

# Ensure that source, header, and library files are present
if (NOT MAIN_SOURCE OR NOT LIB_SOURCE OR NOT HEADER_SOURCE)
    message(FATAL_ERROR "Source files not found!")
endif()

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found !")
endif ()

#------------------------------- MAIN EXECUTABLE -------------------------------

# Define the main application executable
add_executable(fusion_vision
        ${MAIN_FILE}       # Entry point
        ${MAIN_SOURCE}     # All source files
        ${HEADER_SOURCE}   # All header files
        ${LIB_SOURCE}      # All library headers
)

# Find the Freenect2 library (for Kinect2 sensor)
find_library(FREENECT2_LIB freenect2 PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Link the libraries to the main executable
target_link_libraries(fusion_vision
        ${FREENECT2_LIB}   # Kinect2 support
        ${OpenCV_LIBS}     # OpenCV libraries
        ${Boost_LIBRARIES}
)

add_test(NAME Main COMMAND fusion_vision)

#------------------------------- BUILD CONFIGURATION -------------------------------


#------------------------------- UNIT TEST SETUP -------------------------------

# Fetch and include GoogleTest for unit testing
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

# Ensure shared CRT for cross-library compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Download and make GoogleTest available
FetchContent_MakeAvailable(googletest)

# Define the main test file entry point
set(MAIN_TEST_FILE test/device/device_manager_test.cpp)

# Define the test executable
add_executable(unit_test
        ${MAIN_TEST_FILE}   # Main test file
        ${MAIN_SOURCE}      # All source files
        ${HEADER_SOURCE}    # All header files
        ${LIB_SOURCE}       # All library headers
)

# Link GoogleTest and other necessary libraries to the test executable
target_link_libraries(unit_test
        PRIVATE
        GTest::gtest_main   # GoogleTest main function
        ${OpenCV_LIBS}      # OpenCV libraries
        ${FREENECT2_LIB}    # Kinect2 support
)

# Enable testing support in CMake
enable_testing()

# Define a general test case
add_test(NAME GeneralTest COMMAND unit_test)

#------------------------------- UNIT TEST SETUP -------------------------------
