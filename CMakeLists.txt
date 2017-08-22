cmake_minimum_required(VERSION 3.6)
project(solar_system)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$cmake_modules")

set(SOURCE_FILES main.cpp Window.cpp Window.h)
add_executable(solar_system ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(solar_system ${SDL2_LIBRARIES})