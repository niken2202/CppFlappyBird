cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
project (flappybird)

PKG_SEARCH_MODULE(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED SDL_image)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS})

add_executable(
flappybird
Bird.cpp  CMakeLists.txt  CppFlappy.h  Makefile  Pipe.h     World.h
Bird.h    CppFlappy.cpp   main.cpp     Pipe.cpp  World.cpp

)
target_link_libraries(flappybird ${SDL2_LIBRARIES} ${SDL_IMAGE_LIBRARIES})
