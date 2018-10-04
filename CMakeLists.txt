cmake_minimum_required(VERSION 2.8)

project(processing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include(FindPkgConfig)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
#add_executable(processing.exe processing.cpp )

find_package(ROOT REQUIRED)
include_directories(SYSTEM ${ROOT_INCLUDE_DIR})
add_executable(${PROJECT_NAME} "processing.cpp" ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${ROOT_LIBRARIES})
