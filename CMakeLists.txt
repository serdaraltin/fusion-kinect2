cmake_minimum_required(VERSION 3.29)
project(fusion_vision)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

#------------------------------- BUILD -------------------------------
# Include directories for header files
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include  # Include path for project headers
        ${CMAKE_CURRENT_SOURCE_DIR}/lib      # Include path for library headers
)


# Define the main executable for the project
add_executable(fusion_vision
        src/main.cpp
        src/device/device_manager.cpp
        include/device/device_manager.h
        include/logger/console_logger.h
        src/logger/console_logger.cpp
        include/logger/logger.h
        lib/libfreenect2/logger.h
        include/config/config.h
        include/debug/status.h
)

# Locate the Freenect2 library
find_library(FREENECT2_LIBRARY freenect2 PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(fusion_vision
        ${FREENECT2_LIBRARY}  # Link the Freenect2 library
)

# Find and link required libraries
find_package(OpenGL REQUIRED)  # OpenGL
find_package(glfw3 REQUIRED)    # GLFW

# Link libraries to the main executable
target_link_libraries(fusion_vision
        ${OpenCV_LIBS}            # OpenCV libraries
        ${FREENECT2_LIB}         # Freenect2 libraries
)

# Find and include OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})  # Include OpenCV headers

#------------------------------- BUILD -------------------------------


#------------------------------- UNIT TEST ---------------------------

# Include FetchContent module for downloading external dependencies
include(FetchContent)

# Fetch and configure Catch2 for unit testing
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.x  # Specify the version of Catch2
)

# Make Catch2 available for the project
FetchContent_MakeAvailable(catch2)

# Define a separate executable for unit tests using Catch2
add_executable(fusion_vision_test
        tests/device/device_manager_test.cpp
        include/device/device.h)
target_link_libraries(fusion_vision_test PRIVATE Catch2::Catch2)  # Link Catch2 for testing
enable_testing()
add_test(NAME DeviceManager COMMAND fusion_vision_test)

#------------------------------- UNIT TEST ---------------------------