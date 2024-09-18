cmake_minimum_required(VERSION 3.29)
project(fusion_vision)

set(CMAKE_CXX_STANDARD 20)

add_executable(fusion_vision src/main.cpp
        src/device/device.cpp
        include/device/device.h
)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(fusion_vision
        ${OpenCV_LIBS}
        ${FREENECT2_LIB}
)

#add include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib)


find_library(FREENECT2_LIBRARY freenect2 PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(fusion_vision ${FREENECT2_LIBRARY})


#set(OpenNI_DIR /path/to/openni) # OpenNI'nin kurulu olduğu dizin

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(fusion_vision ${OpenCV_LIBS})

#find_package(OpenNI REQUIRED)
#include_directories(${OpenNI_INCLUDE_DIRS})
#target_link_libraries(fusion_vision ${OpenNI_LIBRARIES})