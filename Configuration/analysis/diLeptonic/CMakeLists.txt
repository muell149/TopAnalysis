project(Wolf CXX)

cmake_minimum_required( VERSION 2.5 )
cmake_policy(SET CMP0003 NEW)

set(CMAKE_MODULE_PATH ${${PROJECT_NAME}_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH} 
    CACHE PATH "Path to CMake's Modules" FORCE)

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})

#set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-as-needed")
set(ROOT_LIBRARIES ${ROOT_LIBRARIES} -lGenVector -lHistPainter)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wno-vla -O2 -g -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -pedantic -Wno-vla -O0 -g -std=c++0x")
add_definitions(-DSTANDALONE_COMPILE)

include_directories(src)
add_subdirectory(src) 

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}" CACHE PATH "EXECUTABLE_OUTPUT_PATH" FORCE)
